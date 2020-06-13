package com.food_service.data;

import com.food_service.logic.Administrators;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Administrators {
    
    private final Connection_db db;
    
    private static Dao_Administrators _instance;
    
    public static Dao_Administrators instance(){
        if(_instance==null){
            _instance = new Dao_Administrators();
        }
        return _instance;
    }
    
    private Dao_Administrators(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM administrators WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Administrador no existe");
        }
    }
    
    public Administrators get(int id) throws Exception{
        String sql = "SELECT * FROM administrators WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_administrators(rs);
        }else{
            throw new Exception("Administrador no existe.");
        }
    }
    
    public Administrators getbyUserName(String userName) throws Exception {
        String sql = "SELECT * FROM administrators WHERE user_name='%s'";
        sql = String.format(sql, userName);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_administrators(rs);
        }else{
            throw new Exception("Administrador no existe.");
        }
    }
    
    public List<Administrators> getAll() throws SQLException{
        List<Administrators> li = new ArrayList<>();
        String sql = "SELECT * FROM administrators";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_administrators(rs));
        }
        return li;
    }
    
    public void add(Administrators p) throws Exception{
        String sql="INSERT INTO administrators (user_name, password, name, email, administrator_status) "
                + "VALUES('%s', '%s', '%s', '%s', %d)";
        sql=String.format(sql, p.getUserName(), 
                                        p.getPassword(), 
                                        p.getName(), 
                                        p.getEmail(),
                                        p.getAdministratorStatus().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Administrador ya existe");
        }
    }
    
    public void update(Administrators p) throws Exception{
        String sql="UPDATE administrators SET user_name='%s',  password='%s', name='%s', "+
                "email='%s', administrator_status='%s', client where name='%s";
        sql=String.format(sql, p.getUserName(), 
                                        p.getPassword(),
                                        p.getName(),
                                        p.getEmail(),
                                        p.getAdministratorStatus().getId(),
                                        p.getName());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Administrador no existe");
        }
    }

    private Administrators render_administrators(ResultSet rs){
        try {
            Administrators p = new Administrators();
            p.setId(rs.getInt("id"));
            p.setUserName(rs.getString("user_name"));
            p.setPassword(rs.getString("password"));
            p.setName(rs.getString("name"));
            p.setEmail(rs.getString("email"));
            p.setAdministratorStatus(Dao_Administrator_Status.instance().get(p.getId()));
            return p;
        } catch (Exception ex ) {
            return null;
        }
    }
    
    public void close(){}

}
