package com.food_service.data;

import com.food_service.logic.Details;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Details {
    
    private final Connection_db db;
    
    private static Dao_Details _instance;
    
    public static Dao_Details instance(){
        if(_instance==null){
            _instance = new Dao_Details();
        }
        return _instance;
    }
    
    private Dao_Details(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM details WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Detalle no existe");
        }
    }
    
    public Details get(int id) throws Exception{
        String sql = "SELECT * FROM details WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_details(rs);
        }else{
            throw new Exception("Detalle no existe.");
        }
    }
    
    public List<Details> getAll() throws SQLException{
        List<Details> li = new ArrayList<>();
        String sql = "SELECT * FROM details";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_details(rs));
        }
        return li;
    }
    
    public List<Details> getByAdditional(Integer idAdditional) throws SQLException{
        List<Details> li = new ArrayList<>();
        String sql = "SELECT * FROM details where additional="+idAdditional;
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_details_2(rs));
        }
        return li;
    }
    
    public void add(Details p) throws Exception{
        String sql="INSERT INTO order_status (name) "
                + "VALUES('%s', %f, %d)";
        sql=String.format(sql, p.getName(), p.getPrice(), p.getAdditionals().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Detalle ya existe");
        }
    }
    
    public void update(Details p) throws Exception{
        String sql="UPDATE order_status SET name='%s' price=%f, additional=%d where name='%s'";
        sql=String.format(sql,
                p.getName(),
                p.getPrice(),
                p.getAdditionals(),
                p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Estado de Orden ya existe");
        }
    }

    private Details render_details(ResultSet rs){
        try {
            Details p = new Details();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));
            p.setPrice(rs.getDouble("price"));
            p.setAdditionals(Dao_Additionals.instance().get(rs.getInt("additional")));
            return p;
        } catch (Exception ex) {
            return null;
        }
    }
    
    private Details render_details_2(ResultSet rs){
        try {
            Details p = new Details();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));
            p.setPrice(rs.getDouble("price"));
            //p.setAdditionals(Dao_Additionals.instance().get(rs.getInt("additional")));
            return p;
        } catch (Exception ex) {
            return null;
        }
    }
    
    public void close(){}
}
