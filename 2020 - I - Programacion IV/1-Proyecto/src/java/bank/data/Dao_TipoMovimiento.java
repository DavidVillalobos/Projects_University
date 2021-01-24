package bank.data;

import bank.logic.Tipomovimiento;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Dao_TipoMovimiento {
    
    private final Connection_db db;
    
    private static Dao_TipoMovimiento _instance;
    
    public static Dao_TipoMovimiento instance(){
        if(_instance==null){
            _instance = new Dao_TipoMovimiento();
        }
        return _instance;
    }
    
    private Dao_TipoMovimiento(){
        this.db = Connection_db.instance();
    }
    
    public void delete(Tipomovimiento p) throws Exception{
        String sql="DELETE FROM tipomovimiento WHERE idTipoMovimiento=%s";
        sql = String.format(sql, p.getIdTipoMovimiento());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("TipoMovimiento no existe");
        }
    }
    
    public Tipomovimiento get(Integer idTipoMovimiento) throws Exception{
        String sql = "SELECT * FROM tipomovimiento WHERE idTipoMovimiento=%s";
        sql = String.format(sql,idTipoMovimiento);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_TipoMovimiento(rs);
        }
        else{
            throw new Exception("TipoMovimiento no existe.");
        }
    }
    
    public List<Tipomovimiento> getAll() throws SQLException{
        List<Tipomovimiento> l = new ArrayList<>();
        String sql = "SELECT * FROM tipomovimiento";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_TipoMovimiento(rs));
        }
        return l;
    }
    
    public void add(Tipomovimiento p) throws Exception{
        String sql="INSERT INTO tipomovimiento(idTipoMovimiento, nombre)"
                + "VALUES(%s,'%s')";
        sql=String.format(sql, p.getIdTipoMovimiento(), p.getNombre());        
        if (db.executeUpdate(sql) == 0){
            throw new Exception("TipoMovimiento ya existe");
        }
    }
    
    public void update(Tipomovimiento p) throws Exception{
        String sql="UPDATE tipomovimiento SET nombre=%s WHERE idTipoMovimiento=%s";
        sql=String.format(sql, p.getNombre(), p.getIdTipoMovimiento());   
        if (db.executeUpdate(sql) == 0){
            throw new Exception("TipoMovimiento no existe");
        }
    }

    private Tipomovimiento render_TipoMovimiento(ResultSet rs){
        try {
            Tipomovimiento p = new Tipomovimiento();
            p.setIdTipoMovimiento(rs.getInt("idTipoMovimiento"));
            p.setNombre(rs.getString("nombre"));
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
