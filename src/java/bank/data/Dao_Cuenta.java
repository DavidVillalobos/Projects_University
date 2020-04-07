package bank.data;

import bank.logic.Cliente;
import bank.logic.Cuenta;
import bank.logic.Moneda;
import bank.logic.Usuario;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Dao_Cuenta {
    
    private final Connection_db db;
    
    private static Dao_Cuenta _instance;
    
    public static Dao_Cuenta instance(){
        if(_instance==null){
            _instance = new Dao_Cuenta();
        }
        return _instance;
    }
    
    private Dao_Cuenta(){
        this.db = Connection_db.instance();
    }
    
    public void delete(Cuenta p) throws Exception{
        String sql="DELETE FROM cuenta WHERE idCuenta=%s";
        sql = String.format(sql, p.getIdCuenta());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cuenta no existe");
        }
    }
    
    public Integer lastAccount() throws SQLException{
        String sql="select max(idCuenta) as id from cuenta";
        ResultSet rs = db.executeQuery(sql);
        rs.next();
        return Integer.parseInt(rs.getString("id"));
    }
    
    public Cuenta get(Integer idCuenta) throws Exception{
        String sql = "SELECT * FROM cuenta c "
                + "INNER JOIN cliente cl ON c.cliente = cl.cedula "
                + "INNER JOIN usuario u ON cl.usuario = u.idUsuario "
                + "INNER JOIN moneda m ON c.moneda = m.idMoneda "
                + "WHERE idCuenta = %s";
        sql = String.format(sql,idCuenta);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_cuenta(rs);
        }
        else{
            throw new Exception("Cuenta no existe.");
        }
    }
    
    public List<Cuenta> getAll() throws SQLException{
        List<Cuenta> l = new ArrayList<>();
        String sql = "SELECT * FROM cuenta c "
                + "INNER JOIN cliente cl ON c.cliente = cl.cedula "
                + "INNER JOIN usuario u ON cl.usuario = u.idUsuario "
                + "INNER JOIN moneda m ON c.moneda = m.idMoneda";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_cuenta(rs));
        }
        return l;
    }
    
    public void add(Cuenta p) throws Exception{
        String sql="INSERT INTO cuenta(saldo, limite, cliente, moneda)"
                + " VALUES(%s,%s,'%s','%s')";
        sql=String.format(sql,
                p.getSaldo(),
                p.getLimite(),
                p.getCliente().getCedula(),
                p.getMoneda().getIdMoneda());        
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cuenta ya existe");
        }
    }
    
    public void update(Cuenta p) throws Exception{
        String sql="UPDATE cuenta SET saldo=%s, limite=%s, cliente='%s', moneda='%s'"
                + " WHERE idCuenta=%s";
        sql=String.format(sql,
                p.getSaldo(),
                p.getLimite(),
                p.getCliente().getCedula(),
                p.getMoneda().getIdMoneda(),
                p.getIdCuenta());   
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Cuenta no existe");
        }
    }

    private Cuenta render_cuenta(ResultSet rs){
        try {
            Cliente p = new Cliente();
            Usuario u = new Usuario();
            Moneda m = new Moneda();
            Cuenta c = new Cuenta();
            u.setIdUsuario(rs.getString("idUsuario"));
            u.setPassword(rs.getString("password"));
            u.setTipo(rs.getBoolean("tipo"));
            p.setCedula(rs.getString("cedula"));
            p.setNombre(rs.getString("nombre"));
            p.setTelefono(rs.getInt("telefono"));
            p.setUsuario(u);
            m.setIdMoneda(rs.getString("idMoneda"));
            m.setValorColones(rs.getBigDecimal("valorColones"));
            c.setIdCuenta(rs.getInt("idCuenta"));
            c.setSaldo(rs.getDouble("saldo"));
            c.setLimite(rs.getDouble("limite"));
            c.setCliente(p);
            c.setMoneda(m);
            return c;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}
}
