package bank.data;

import bank.logic.Usuario;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Dao_Usuario {
    
    private final Connection_db db;
    
    private static Dao_Usuario _instance;
    
    public static Dao_Usuario instance(){
        if(_instance == null){
            _instance = new Dao_Usuario();
        }
        return _instance;
    }

    private Dao_Usuario() {
        this.db = Connection_db.instance();
    }
         
    public void delete(Usuario p) throws Exception{
        String sql="DELETE FROM Usuario WHERE idUsuario='%s'";
        sql = String.format(sql, p.getIdUsuario());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Usuario no existe");
        }
    }
    
    public Usuario get(String id) throws Exception{
        String sql = "SELECT * FROM Usuario WHERE idUsuario='%s'";
        sql = String.format(sql,id);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_usuario(rs);
        }
        else{
            throw new Exception("Usuario no existe.");
        }
    }
    
    public List<Usuario> getAll() throws SQLException{
        List<Usuario> l = new ArrayList<>();
        String sql = "SELECT * FROM Usuario";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_usuario(rs));
        }
        return l;
    }
    
    public void add(Usuario p) throws Exception{
        String sql="INSERT INTO Usuario (idUsuario, password, tipo)"
                + "VALUES('%s','%s',%s)";
        sql=String.format(sql, 
                p.getIdUsuario(),
                p.getPassword(),
                p.getTipo());        
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Usuario ya existe");
        }
    }
    
    public void update(Usuario p) throws Exception{
        String sql="UPDATE Usuario set password='%s', tipo=%s"
                + " where idUsuario='%s'";
        sql=String.format(sql,
                p.getPassword(),
                p.getTipo(),
                p.getIdUsuario());   
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Usuario no existe");
        }
    }

    private Usuario render_usuario(ResultSet rs){
        try {
            Usuario p= new Usuario();
            p.setIdUsuario(rs.getString("idUsuario"));
            p.setPassword(rs.getString("password"));
            p.setTipo(rs.getBoolean("tipo"));
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){} 
}
