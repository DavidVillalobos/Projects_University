package com.food_service.data;

import com.food_service.logic.ClientDish;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Client_Dish {
    
    private final Connection_db db;
    
    private static Dao_Client_Dish _instance;
    
    public static Dao_Client_Dish instance(){
        if(_instance==null){
            _instance = new Dao_Client_Dish();
        }
        return _instance;
    }
    
    private Dao_Client_Dish(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM client_dish WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente_Platillo no existe");
        }
    }
    
    public ClientDish get(int id) throws Exception{
        String sql = "SELECT * FROM client_dish WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_client_dish(rs);
        }else{
            throw new Exception("Cliente_Platillo no existe.");
        }
    }
    
    public List<ClientDish> getAll() throws Exception{
        List<ClientDish> li = new ArrayList<>();
        String sql = "SELECT * FROM client_dish";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_client_dish(rs));
        }
        return li;
    }
    
     List<ClientDish> getDishesByOrder(int id_order) throws Exception {
            List<ClientDish> li = new ArrayList<>();
            String sql = "SELECT * FROM client_dish d where d.order=%d";
            sql=String.format(sql, id_order);
            ResultSet rs = db.executeQuery(sql);
            
            while(rs.next()){
                li.add(render_client_dish(rs));
            }
            return li;
     }
    
    public void add(ClientDish p) throws Exception{
        String sql="INSERT INTO client_dish (quantity, dish, order) "
                + "VALUES(%d, %d, %d)";
        sql=String.format(sql, p.getQuantity(), p.getDishes().getId(), p.getOrders().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente_Platillo ya existe");
        }
    }
    
    public void update(ClientDish p) throws Exception{
        String sql="UPDATE client_dish SET quantity=%d, dish=%d, order=%d where id=%d";
        sql=String.format(sql, p.getQuantity(), p.getDishes().getId(), p.getOrders().getId(), p.getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente_Platillo no existe");
        }
    }

    private ClientDish render_client_dish(ResultSet rs){
        try {
            ClientDish p = new ClientDish();
            p.setId(rs.getInt("id"));
            p.setQuantity(rs.getInt("quantity"));
            p.setDishes(Dao_Dishes.instance().get(rs.getInt("dish")));
            return p;
        } catch (Exception ex) {
            return null;
        }
    }
    
    public void close(){}
}
