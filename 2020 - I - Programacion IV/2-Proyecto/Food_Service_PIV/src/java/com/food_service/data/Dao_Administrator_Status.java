package com.food_service.data;

import com.food_service.logic.AdministratorStatus;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */

public class Dao_Administrator_Status {
    
    private final Connection_db db;
    
    private static Dao_Administrator_Status _instance;
    
    public static Dao_Administrator_Status instance(){
        if(_instance==null){
            _instance = new Dao_Administrator_Status();
        }
        return _instance;
    }
    
    private Dao_Administrator_Status(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM administrator_status WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Orden no existe");
        }
    }
    
    public AdministratorStatus get(int id) throws Exception{
        String sql = "SELECT * FROM administrator_status WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_administrador_status(rs);
        }else{
            throw new Exception("Estado de Orden no existe.");
        }
    }
    
    public List<AdministratorStatus> getAll() throws SQLException{
        List<AdministratorStatus> li = new ArrayList<>();
        String sql = "SELECT * FROM administrator_status";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_administrador_status(rs));
        }
        return li;
    }
    
    public void add(AdministratorStatus p) throws Exception{
        String sql="INSERT INTO administrator_status (name) "
                + "VALUES('%s')";
        sql=String.format(sql, p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Estado de Orden ya existe");
        }
    }
    
    public void update(AdministratorStatus p) throws Exception{
        String sql="UPDATE administrator_status SET name='%s' where name='%s'";
        sql=String.format(sql,
                p.getName(),
                p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Estado de Orden ya existe");
        }
    }

    private AdministratorStatus render_administrador_status(ResultSet rs){
        try {
            AdministratorStatus p = new AdministratorStatus();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));            
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
