package bank.data;

import bank.logic.Moneda;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Dao_Moneda {
    
    private final Connection_db db;
    
    private static Dao_Moneda _instance;
    
    public static Dao_Moneda instance(){
        if(_instance==null){
            _instance = new Dao_Moneda();
        }
        return _instance;
    }
    
    private Dao_Moneda(){
        this.db = Connection_db.instance();
    }
    
    public void delete(Moneda p) throws Exception{
        String sql="DELETE FROM moneda WHERE idMoneda='%s'";
        sql = String.format(sql, p.getIdMoneda());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Moneda no existe");
        }
    }
    
    public Moneda get(String idMoneda) throws Exception{
        String sql = "SELECT * FROM moneda WHERE idMoneda='%s'";
        sql = String.format(sql,idMoneda);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_moneda(rs);
        }
        else{
            throw new Exception("Moneda no existe.");
        }
    }
    
    public List<Moneda> getAll() throws SQLException{
        List<Moneda> l = new ArrayList<>();
        String sql = "SELECT * FROM moneda";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_moneda(rs));
        }
        return l;
    }
    
    public void add(Moneda p) throws Exception{
        String sql="INSERT INTO moneda(idMoneda, valorColones)"
                + "VALUES('%s',%s)";
        sql=String.format(sql, p.getIdMoneda(), p.getValorColones());        
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Moneda ya existe");
        }
    }
    
    public void update(Moneda p) throws Exception{
        String sql="UPDATE moneda SET valorColones=%s WHERE idMoneda='%s'";
        sql=String.format(sql, p.getValorColones(), p.getIdMoneda());   
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Moneda no existe");
        }
    }

    private Moneda render_moneda(ResultSet rs){
        try {
            Moneda p = new Moneda();
            p.setIdMoneda(rs.getString("idMoneda"));
            p.setValorColones(rs.getDouble("valorColones"));
            p.setNombreMoneda(rs.getString("nombreMoneda"));
            p.setInteres(rs.getDouble("interes"));
            return p;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
