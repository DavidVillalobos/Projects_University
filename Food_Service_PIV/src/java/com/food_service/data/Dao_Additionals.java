package com.food_service.data;

import com.food_service.logic.Additionals;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Additionals {
    
    private final Connection_db db;
    
    private static Dao_Additionals _instance;
    
    public static Dao_Additionals instance(){
        if(_instance==null){
            _instance = new Dao_Additionals();
        }
        return _instance;
    }
    
    private Dao_Additionals(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM additionals WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Adicional no existe");
        }
    }
    
    public Additionals get(int id) throws Exception{
        String sql = "SELECT * FROM additionals WHERE name=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_additionals(rs);
        }else{
            throw new Exception("Adicional no existe.");
        }
    }
    
    public List<Additionals> getAll() throws SQLException{
        List<Additionals> li = new ArrayList<>();
        String sql = "SELECT * FROM additionals";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_additionals(rs));
        }
        return li;
    }
    
    public List<Additionals> getByDish(String idDish) throws SQLException{
        List<Additionals> li = new ArrayList<>();
        String sql = "SELECT * FROM additionals where dish="+idDish;
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_additionals(rs));
        }
        return li;
    }
    
    public void add(Additionals p) throws Exception{
        String sql="INSERT INTO additionals (name, type, mandatory, dish) "
                + "VALUES('%s', %b, %b, %d)";
        sql=String.format(sql, p.getName(), p.getType(), p.getMandatory(), p.getDishes().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Adicional ya existe");
        }
    }
    
    public void update(Additionals p) throws Exception{
        String sql="UPDATE additionals SET name='%s', type=%b, mandatory=%b, dish=%d, where name='%s";
        sql=String.format(sql,
                p.getName(),
                p.getType(), 
                p.getMandatory(),
                p.getDishes().getId(),
                p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Adicional no existe");
        }
    }

    private Additionals render_additionals(ResultSet rs){
        try {
            Additionals p = new Additionals();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));
            p.setType(rs.getShort("type"));
            p.setMandatory(rs.getShort("mandatory"));
            p.setDishes(Dao_Dishes.instance().get(rs.getInt("dish")));
            return p;
        } catch (Exception ex) {
            return null;
        }
    }
    
    public void close(){}
}
