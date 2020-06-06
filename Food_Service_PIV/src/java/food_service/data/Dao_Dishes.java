package food_service.data;

import food_service.logic.Dishes;
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
    
    public void delete(String name) throws Exception{
        String sql="DELETE FROM dishes WHERE name='%s'";
        sql = String.format(sql, name);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Platillo no existe");
        }
    }
    
    public Dishes get(String name) throws Exception{
        String sql = "SELECT * FROM dishes WHERE name='%s'";
        sql = String.format(sql, name);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_dishes(rs);
        }else{
            throw new Exception("Platillo no existe.");
        }
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
        String sql="INSERT INTO dishes (name, price, description, categorie) "
                + "VALUES('%s', %f, '%s', %d)";
        sql=String.format(sql, p.getName(), p.getPrice(), p.getDecription(), p.getCategories().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Platillo ya existe");
        }
    }
    
    public void update(Dishes p) throws Exception{
        String sql="UPDATE dishes SET name='%s', price=%b, description=%b, categorie=%d, where name='%s";
        sql=String.format(sql,
                p.getName(),
                p.getPrice(), 
                p.getDecription(), 
                p.getCategories().getId(),
                p.getName()); 
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
            p.setDecription(rs.getString("description"));
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
