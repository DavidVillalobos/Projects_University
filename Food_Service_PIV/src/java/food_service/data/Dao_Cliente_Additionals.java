package food_service.data;

import food_service.logic.ClienteAdditionals;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Cliente_Additionals {
    
    private final Connection_db db;
    
    private static Dao_Cliente_Additionals _instance;
    
    public static Dao_Cliente_Additionals instance(){
        if(_instance==null){
            _instance = new Dao_Cliente_Additionals();
        }
        return _instance;
    }
    
    private Dao_Cliente_Additionals(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM cliente_additionals WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente Adicional no existe");
        }
    }
    
    public ClienteAdditionals get(int id) throws Exception{
        String sql = "SELECT * FROM cliente_additionals WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_cliente_additionals(rs);
        }else{
            throw new Exception("Cliente Adicional no existe.");
        }
    }
    
    public List<ClienteAdditionals> getAll() throws SQLException{
        List<ClienteAdditionals> li = new ArrayList<>();
        String sql = "SELECT * FROM cliente_additionals";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            li.add(render_cliente_additionals(rs));
        }
        return li;
    }
    
    public void add(ClienteAdditionals p) throws Exception{
        String sql="INSERT INTO cliente_additionals (additional, client_dish) "
                + "VALUES(%d, %d)";
        sql=String.format(sql, p.getAdditionals().getId(), p.getClientDish().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente Adicional ya existe");
        }
    }
    
    public void update(ClienteAdditionals p) throws Exception{
        String sql="UPDATE cliente_additionals SET additional=%d, client_dish=%d, where id=%d";
        sql=String.format(sql, p.getAdditionals().getId(), p.getClientDish().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente Adicional no existe");
        }
    }

    private ClienteAdditionals render_cliente_additionals(ResultSet rs){
        try {
            ClienteAdditionals p = new ClienteAdditionals();
            p.setId(rs.getInt("id"));
            
            
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
