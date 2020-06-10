package com.food_service.data;

import com.food_service.logic.Orders;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Orders {
    
    private final Connection_db db;
    
    private static Dao_Orders _instance;
    
    public static Dao_Orders instance(){
        if(_instance==null){
            _instance = new Dao_Orders();
        }
        return _instance;
    }
    
    private Dao_Orders(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM orders WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Orden no existe");
        }
    }
    
    public Orders get(int id) throws Exception{
        String sql = "SELECT * FROM orders WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_orders(rs);
        }else{
            throw new Exception("Orden no existe.");
        }
    }
    
    public List<Orders> getAll() throws SQLException{
        List<Orders> l = new ArrayList<>();
        String sql = "SELECT * FROM orders";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_orders(rs));
        }
        return l;
    }
    
    public void add(Orders p) throws Exception{
        String sql="INSERT INTO orders (type, orderDate, deleveryDate, asap, total, direction, client, order_status, locations_id) "
                + "VALUES(%b, %dt, %dt, %b, %f, '%s', %d, %d, %d)";
        sql=String.format(sql,
                p.getType(),
                p.getOrderDate(),
                p.getDeliveryDate(),
                p.getAsap(),
                p.getTotal(),
                p.getDirection(),
                p.getClients().getId(),
                p.getOrderStatus().getId(),
                p.getLocations().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Orden ya existe");
        }
    }
    
    public void update(Orders p) throws Exception{
        String sql="UPDATE orders type=%b, orderDate=%dt, deleveryDate=%dt, "+
                "asap=%b, total=%f, direction='%s', client=%d, order_status=%d, locations_id=%d where id=%d";
       sql=String.format(sql,
                p.getType(),
                p.getOrderDate(),
                p.getDeliveryDate(),
                p.getAsap(),
                p.getTotal(),
                p.getDirection(),
                p.getClients().getId(),
                p.getOrderStatus().getId(),
                p.getLocations().getId(),
                p.getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Orden ya existe");
        }
    }

    private Orders render_orders(ResultSet rs){
        try {
            Orders p = new Orders();
            p.setId(rs.getInt("id"));
            p.setType(rs.getShort("type"));
            p.setOrderDate(rs.getDate("orderDate"));
            p.setDeliveryDate(rs.getDate("deliveryDate"));
            p.setAsap(rs.getShort("asap"));
            p.setTotal(rs.getDouble("total"));
            p.setDirection(rs.getString("direction"));
            p.setClients(Dao_Clients.instance().getById(rs.getInt("client")));
            p.setOrderStatus(Dao_Order_Status.instance().get(rs.getInt("order_status")));
            p.setLocations(Dao_Locations.instance().get(rs.getInt("Locations_id")));   
            p.setClientDishList(Dao_Client_Dish.instance().getDishesByOrder(rs.getInt("client")));
            return p; 
          } catch (Exception ex) {
            return null;
        }
    }
    
    public void close(){}
}
