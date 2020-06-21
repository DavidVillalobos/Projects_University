package com.food_service.data;

import com.food_service.logic.Clients;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Clients {
    
    private final Connection_db db;
    
    private static Dao_Clients _instance;
    
    public static Dao_Clients instance(){
        if(_instance==null){
            _instance = new Dao_Clients();
        }
        return _instance;
    }
    
    private Dao_Clients(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM clients WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente no existe");
        }
    }
    
    public Clients get(String email) throws Exception{
        String sql = "SELECT * FROM clients WHERE email='%s'";
        sql = String.format(sql, email);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_clients(rs);
        }else{
            throw new Exception("Cliente no existe.");
        }
   }
    
   public Clients getById(int id) throws Exception{
        String sql = "SELECT * FROM clients WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_clients(rs);
        }else{
            throw new Exception("Cliente no existe.");
        }
    }
    
    public List<Clients> getAll() throws SQLException{
        List<Clients> l = new ArrayList<>();
        String sql = "SELECT * FROM clients";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_clients(rs));
        }
        return l;
    }
    
    public void add(Clients p) throws Exception{
        String sql="INSERT INTO clients (name, telephone, last_name, password, email) "
                + "VALUES('%s','%s','%s','%s','%s')";
        sql=String.format(sql,
                p.getName(),
                p.getTelephone(),
                p.getLastName(),
                p.getPassword(),
                p.getEmail()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente ya existe");
        }
    }
    
    public Clients getLast() throws SQLException, Exception{
        String sql = "SELECT * FROM clients WHERE id=( SELECT MAX(id) FROM clients )";
        
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_clients(rs);
        }else{
            throw new Exception("Cliente no existe.");
        }
    }
    
    public void update(Clients p) throws Exception{
        String sql="UPDATE clients SET name='%s', telephone='%s', last_name='%s'"
                + " password='%s', email='%s' where email='%s'";
        sql=String.format(sql,
                p.getName(),
                p.getTelephone(),
                p.getLastName(),
                p.getPassword(),
                p.getEmail(), 
                p.getEmail()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente ya existe");
        }
    }

    private Clients render_clients(ResultSet rs){
        try {
            Clients p = new Clients();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));
            p.setTelephone(rs.getString("telephone"));
            p.setLastName(rs.getString("last_name"));
            p.setPassword(rs.getString("password"));
            p.setEmail(rs.getString("email"));
            return p;
          } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
