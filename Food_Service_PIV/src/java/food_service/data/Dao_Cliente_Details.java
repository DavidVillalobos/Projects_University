package food_service.data;

import food_service.logic.ClienteDetails ;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Dao_Cliente_Details {
    
    private final Connection_db db;
    
    private static Dao_Cliente_Details _instance;
    
    public static Dao_Cliente_Details instance(){
        if(_instance==null){
            _instance = new Dao_Cliente_Details();
        }
        return _instance;
    }
    
    private Dao_Cliente_Details(){
        this.db = Connection_db.instance();
    }
    
    public void delete(int id) throws Exception{
        String sql="DELETE FROM Cliente_Details WHERE id=%d";
        sql = String.format(sql, id);
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente Detalle no existe");
        }
    }
    
    public ClienteDetails get(int id) throws Exception{
        String sql = "SELECT * FROM Cliente_Details WHERE id=%d";
        sql = String.format(sql, id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_cliente_details(rs);
        }else{
            throw new Exception("Cliente Detalle no existe.");
        }
    }
    
    public List<ClienteDetails > getAll() throws SQLException{
        List<ClienteDetails > l = new ArrayList<>();
        String sql = "SELECT * FROM Cliente_Details";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_cliente_details(rs));
        }
        return l;
    }
    
    public void add(ClienteDetails  p) throws Exception{
        String sql="INSERT INTO Cliente_Details (detail, cliente_additional) "
                + "VALUES(%d, %d)";
        sql=String.format(sql, p.getDetails().getId(), p.getClienteAdditionals().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente Detalle ya existe");
        }
    }
    
    public void update(ClienteDetails  p) throws Exception{
        String sql="UPDATE Cliente_Details SET detail=%d, cliente_additional=%d where id=%d";
        sql=String.format(sql,
                p.getDetails().getId(),
                p.getClienteAdditionals().getId()); 
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente Detalle ya existe");
        }
    }

    private ClienteDetails  render_cliente_details(ResultSet rs){
        try {
            ClienteDetails  p = new ClienteDetails ();
            p.setId(rs.getInt("id"));            
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
