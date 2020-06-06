package food_service.data;

import food_service.logic.OrderStatus;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Order_Status {
    
    private final Connection_db db;
    
    private static Dao_Order_Status _instance;
    
    public static Dao_Order_Status instance(){
        if(_instance==null){
            _instance = new Dao_Order_Status();
        }
        return _instance;
    }
    
    private Dao_Order_Status(){
        this.db = Connection_db.instance();
    }
    
    public void delete(OrderStatus p) throws Exception{
        String sql="DELETE FROM order_status WHERE name='%s'";
        sql = String.format(sql, p.getName());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Estado de Orden no existe");
        }
    }
    
    public OrderStatus get(String name) throws Exception{
        String sql = "SELECT * FROM order_status WHERE name='%s'";
        sql = String.format(sql, name);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_order_status(rs);
        }else{
            throw new Exception("Estado de Orden no existe.");
        }
    }
    
    public List<OrderStatus> getAll() throws SQLException{
        List<OrderStatus> li = new ArrayList<>();
        String sql = "SELECT * FROM order_status";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_order_status(rs));
        }
        return li;
    }
    
    public void add(OrderStatus p) throws Exception{
        String sql="INSERT INTO order_status (name) "
                + "VALUES('%s')";
        sql=String.format(sql, p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Estado de Orden ya existe");
        }
    }
    
    public void update(OrderStatus p) throws Exception{
        String sql="UPDATE order_status SET name='%s' where name='%s'";
        sql=String.format(sql,
                p.getName(),
                p.getName()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Estado de Orden ya existe");
        }
    }

    private OrderStatus render_order_status(ResultSet rs){
        try {
            OrderStatus p = new OrderStatus();
            p.setId(rs.getInt("id"));
            p.setName(rs.getString("name"));
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
