package com.food_service.data;

import com.food_service.logic.Dishes;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Dishes {
    
    private final Connection_db db;
    
    private static Dao_Dishes _instance;
    
    public static Dao_Dishes instance(){
        if(_instance==null){
            _instance = new Dao_Dishes();
        }
        return _instance;
    }
    
    private Dao_Dishes(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM dishes WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Platillo no existe");
        }
    }
    
    public Dishes get(int id) throws Exception{
        String sql = "SELECT * FROM dishes WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_dishes(rs);
        }else{
            throw new Exception("Platillo no existe.");
        }
    }
    
    public List<Dishes> getByCategorie(String idCategorie) throws SQLException{
        List<Dishes> li = new ArrayList<>();
        String sql = "SELECT * FROM dishes where categorie="+idCategorie;
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_dishes(rs));
        }
        return li;
    }
    
    public List<Dishes> getAll() throws SQLException{
        List<Dishes> li = new ArrayList<>();
        String sql = "SELECT * FROM dishes";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_dishes(rs));
        }
        return li;
    }
    
    public void add(Dishes p) throws Exception{
        String sql="INSERT INTO dishes (name, price, decription, categorie) "
                + "VALUES('%s', %f, '%s', %d)";
        sql=String.format(sql, p.getName(), p.getPrice(), p.getDecription(), p.getCategories().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Platillo ya existe");
        }
    }
    
    public void update(Dishes p) throws Exception{
        String sql="UPDATE dishes SET name='%s', price=%f, decription='%s' where id=%d";
        sql=String.format(sql,
                p.getName(),
                p.getPrice(), 
                p.getDecription(),
                p.getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Platillo no existe");
        }
    }

    private Dishes render_dishes(ResultSet rs){
        try {
            Dishes p = new Dishes();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));
            p.setPrice(rs.getDouble("price"));
            p.setDecription(rs.getString("decription"));
            p.setCategories(Dao_Categories.instance().get(rs.getInt("categorie")));
            return p;
        } catch (Exception ex) {
            return null;
        }
    }
    
    public void close(){}
}
