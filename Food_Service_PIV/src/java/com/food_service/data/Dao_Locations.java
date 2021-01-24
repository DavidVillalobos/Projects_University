package com.food_service.data;

import com.food_service.logic.Locations;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Locations {
    
    private final Connection_db db;
    
    private static Dao_Locations _instance;
    
    public static Dao_Locations instance(){
        if(_instance==null){
            _instance = new Dao_Locations();
        }
        return _instance;
    }
    
    private Dao_Locations(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM locations WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Ubicacion no existe");
        }
    }
    
    public Locations get(int id) throws Exception{
        String sql = "SELECT * FROM locations WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_locations(rs);
        }else{
            throw new Exception("Ubicacion no existe.");
        }
    }
    
    public List<Locations> getAll() throws SQLException{
        List<Locations> li = new ArrayList<>();
        String sql = "SELECT * FROM locations";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_locations(rs));
        }
        return li;
    }
    
    public void add(Locations p) throws Exception{
        String sql="INSERT INTO locations (name, administrator) "
                + "VALUES('%s', %d)";
        sql=String.format(sql, p.getName(), p.getAdministrators()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Ubicacion ya existe");
        }
    }
    
    public void update(Locations p) throws Exception{
        String sql="UPDATE locations SET name='%s',  administrator=%d where name='%s";
        sql=String.format(sql, p.getName(), 
                                        p.getAdministrators().getId(),
                                        p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Ubicacion no existe");
        }
    }
    
        private Locations render_locations(ResultSet rs){
        try {
            Locations p = new Locations();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));
            p.setAdministrators(Dao_Administrators.instance().get(rs.getInt("id")));
            return p;
        } catch (Exception ex ) {
            return null;
        }
    }
    
    public void close(){}
}
