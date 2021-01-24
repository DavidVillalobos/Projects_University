package com.food_service.data;

import com.food_service.logic.Adresses;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Adresses {
    
    private final Connection_db db;
    
    private static Dao_Adresses _instance;
    
    public static Dao_Adresses instance(){
        if(_instance==null){
            _instance = new Dao_Adresses();
        }
        return _instance;
    }
    
    private Dao_Adresses(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM adresses WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Direccion no existe");
        }
    }
    
    public Adresses get(String name) throws Exception{
        String sql = "SELECT * FROM adresses WHERE name='%s'";
        sql = String.format(sql, name);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_adresses(rs);
        }else{
            throw new Exception("Direccion no existe.");
        }
    }
     
    public Adresses get(int id) throws Exception {
        String sql = "SELECT * FROM adresses WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_adresses(rs);
        }else{
            throw new Exception("Direccion no existe.");
        }
    }
    
    public List<Adresses> getAll() throws SQLException{
        List<Adresses> li = new ArrayList<>();
        String sql = "SELECT * FROM adresses";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_adresses(rs));
        }
        return li;
    }
    
    public void add(Adresses p) throws Exception{
        String sql="INSERT INTO adresses (name, latitude, longitude, address, city, state, country, postcode, client) "
                + "VALUES('%s', %f, %f, '%s', '%s','%s','%s','%s', %d)";
        sql=String.format(sql, p.getName(), 
                                        p.getLatitude(), 
                                        p.getLongitude(), 
                                        p.getAdress(),
                                        p.getCity(), 
                                        p.getState(), 
                                        p.getCountry(), 
                                        p.getPostcode(), 
                                        p.getClients().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Direccion ya existe");
        }
    }
    
    public void update(Adresses p) throws Exception{
        String sql="UPDATE adresses SET name='%s',  latitude=%f, longitude=%f, address='%s', city='%s', state='%s'," +
                " country='%s', postcode='%s', client where name='%s";
        sql=String.format(sql, p.getName(), 
                                        p.getLatitude(), 
                                        p.getLongitude(), 
                                        p.getAdress(),
                                        p.getCity(), 
                                        p.getState(), 
                                        p.getCountry(), 
                                        p.getPostcode(), 
                                        p.getClients().getId(),
                                        p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Direccion no existe");
        }
    }

    private Adresses render_adresses(ResultSet rs){
        try {
            Adresses p = new Adresses();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));
            p.setLatitude(rs.getFloat("latitude"));
            p.setLongitude(rs.getFloat("longitude"));
            p.setAdress(rs.getString("adress"));
            p.setCity(rs.getString("city"));
            p.setState(rs.getString("state"));
            p.setCountry(rs.getString("country"));
            p.setPostcode(rs.getString("postcode"));
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}

}
