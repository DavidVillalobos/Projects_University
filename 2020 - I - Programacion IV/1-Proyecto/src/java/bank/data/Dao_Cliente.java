package bank.data;

import bank.logic.Cliente;
import bank.logic.Usuario;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Dao_Cliente {
    
    private final Connection_db db;
    
    private static Dao_Cliente _instance;
    
    public static Dao_Cliente instance(){
        if(_instance==null){
            _instance = new Dao_Cliente();
        }
        return _instance;
    }
    
    private Dao_Cliente(){
        this.db = Connection_db.instance();
    }
    
    public void delete(Cliente p) throws Exception{
        String sql="DELETE FROM cliente WHERE cedula='%s'";
        sql = String.format(sql, p.getCedula());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente no existe");
        }
    }
    
    public Cliente get(String cedula) throws Exception{
        String sql = "SELECT * FROM cliente c INNER JOIN usuario u "
                + "ON c.usuario = u.idUsuario WHERE cedula='%s'";
        sql = String.format(sql,cedula);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_cliente(rs);
        }
        else{
            throw new Exception("Cliente no existe.");
        }
    }
    
    public List<Cliente> getAll() throws SQLException{
        List<Cliente> l = new ArrayList<>();
        String sql = "SELECT * FROM cliente c INNER JOIN usuario u ON "
                + "c.usuario = u.idUsuario";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_cliente(rs));
        }
        return l;
    }
    
    public void add(Cliente p) throws Exception{
        String sql="INSERT INTO cliente (cedula, nombre, telefono, usuario)"
                + "VALUES('%s','%s',%s,'%s')";
        sql=String.format(sql, 
                p.getCedula(),
                p.getNombre(),
                p.getTelefono(),
                p.getUsuario().getIdUsuario());        
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente ya existe");
        }
    }
    
    public void update(Cliente p) throws Exception{
        String sql="UPDATE cliente SET nombre='%s', telefono=%s, usuario='%s'"
                + " where cedula='%s'";
        sql=String.format(sql,
                p.getNombre(),
                p.getTelefono(),
                p.getUsuario().getIdUsuario(),
                p.getCedula());   
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cliente no existe");
        }
    }

    private Cliente render_cliente(ResultSet rs){
        try {
            Cliente p = new Cliente();
            Usuario u = new Usuario();
            u.setIdUsuario(rs.getString("idUsuario"));
            u.setPassword(rs.getString("password"));
            u.setTipo(rs.getBoolean("tipo"));
            p.setCedula(rs.getString("cedula"));
            p.setNombre(rs.getString("nombre"));
            p.setTelefono(rs.getInt("telefono"));
            p.setUsuario(u);
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
