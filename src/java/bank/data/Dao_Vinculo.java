package bank.data;


import bank.logic.Cliente;
import bank.logic.Cuenta;
import bank.logic.Vinculo;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Dao_Vinculo {
    
    private final Connection_db db;
    
    private static Dao_Vinculo _instance;
    
    public static Dao_Vinculo instance(){
        if(_instance==null){
            _instance = new Dao_Vinculo();
        }
        return _instance;
    }
    
    private Dao_Vinculo(){
        this.db = Connection_db.instance();
    }
    
    public void delete(Vinculo p) throws Exception{
        String sql="DELETE FROM vinculo WHERE idVinculo=%s";
        sql = String.format(sql, p.getIdVinculo());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Vinculo no existe");
        }
    }
    
    public Vinculo get(Integer idVinculo) throws Exception{
        String sql = "SELECT * FROM vinculo WHERE idVinculo = %s";
        sql = String.format(sql,idVinculo);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_vinculo(rs);
        }
        else{
            throw new Exception("Vinculo no existe.");
        }
    }
    
    public List<Vinculo> getAll() throws SQLException, Exception{
        List<Vinculo> l = new ArrayList<>();
        String sql = "SELECT * FROM vinculo";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_vinculo(rs));
        }
        return l;
    }
    
    public void add(Vinculo p) throws Exception{
        String sql="INSERT INTO vinculo(cliente, cuenta) VALUES('%s',%s)";
        sql=String.format(sql,
                p.getCliente().getCedula(),
                p.getCuenta().getIdCuenta());        
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Vinculo ya existe");
        }
    }
    
    public void update(Vinculo p) throws Exception{
        String sql="UPDATE vinculo SET cliente='%s', cuenta=%s"
                + " WHERE idVinculo=%s";
        sql=String.format(sql,
                p.getCliente().getCedula(),
                p.getCuenta().getIdCuenta(),
                p.getIdVinculo());   
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Vinculo no existe");
        }
    }

    private Vinculo render_vinculo(ResultSet rs) throws Exception{
        try {
            Vinculo v = new Vinculo();
            Cliente p = Dao_Cliente.instance().get(rs.getString("cliente"));
            Cuenta c = Dao_Cuenta.instance().get(rs.getInt("cuenta"));
            v.setIdVinculo(rs.getInt("idVinculo"));
            v.setCliente(p);
            v.setCuenta(c);
            return v;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
