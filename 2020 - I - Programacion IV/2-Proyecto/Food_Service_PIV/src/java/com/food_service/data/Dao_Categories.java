package com.food_service.data;

import com.food_service.logic.Categories;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Categories {
    
    private final Connection_db db;
    
    private static Dao_Categories _instance;
    
    public static Dao_Categories instance(){
        if(_instance==null){
            _instance = new Dao_Categories();
        }
        return _instance;
    }
    
    private Dao_Categories(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM categories WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Categoria no existe");
        }
    }
    
    public Categories get(int id) throws Exception{
        String sql = "SELECT * FROM categories WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_categories(rs);
        }else{
            throw new Exception("Categoria no existe.");
        }
    }
    
    public List<Categories> getAll() throws SQLException{
        List<Categories> l = new ArrayList<>();
        String sql = "SELECT * FROM categories";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_categories(rs));
        }
        return l;
    }
    
    public void add(Categories p) throws Exception{
        String sql="INSERT INTO categories (name) "
                + "VALUES('%s')";
        sql=String.format(sql, p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Categoria ya existe");
        }
    }
    
    public void update(Categories p) throws Exception{
        String sql="UPDATE categories SET name='%s' where id=%d";
        sql=String.format(sql,
                p.getName(),
                p.getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Categoria ya existe");
        }
    }

    private Categories render_categories(ResultSet rs){
        try {
            Categories p = new Categories();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));            
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
