package bank.data;

import bank.logic.Cuenta;
import bank.logic.Movimiento;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Dao_Movimiento {
    
    private final Connection_db db;
    
    private static Dao_Movimiento _instance;
    
    public static Dao_Movimiento instance(){
        if(_instance==null){
            _instance = new Dao_Movimiento();
        }
        return _instance;
    }
    
    private Dao_Movimiento(){
        this.db = Connection_db.instance();
    }
    
    public void delete(Movimiento p) throws Exception{
        String sql="DELETE FROM vinculo WHERE idMovimiento=%s";
        sql = String.format(sql, p.getIdMovimiento());
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Moviimiento no existe");
        }
    }
    
    public Movimiento get(Integer idMovimiento) throws Exception{
        String sql = "SELECT * FROM movimiento WHERE idMovimiento = %s";
        sql = String.format(sql,idMovimiento);
        ResultSet rs = db.executeQuery(sql);
        if(rs.next()){
            return render_movimiento(rs);
        }
        else{
            throw new Exception("Movimiento no existe.");
        }
    }
    
    public List<Movimiento> getAll() throws SQLException, Exception{
        List<Movimiento> l = new ArrayList<>();
        String sql = "SELECT * FROM movimiento";
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_movimiento(rs));
        }
        return l;
    }
    
    public List<Movimiento> getRecentMovements(Cuenta c) throws SQLException, Exception{
        List<Movimiento> l = new ArrayList<>();
        String sql = "SELECT * FROM movimiento WHERE ((cuentaOrigen=%d and tipo=1) or (cuentaDestino=%d and tipo=2));";
        sql = String.format(sql, c.getIdCuenta(), c.getIdCuenta());
        int x = 8;
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){}
        while(rs.previous() && x > 0){
            l.add(render_movimiento(rs)); x--;
        }
        return l;
    }
    
    public List<Movimiento> getMovementsByDate(Cuenta c, Date fecha) throws SQLException, Exception{
        List<Movimiento> l = new ArrayList<>();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        String fechaString = sdf.format(fecha);
        String sql = "SELECT * FROM movimiento WHERE (cuentaOrigen=%d AND fecha='%s' AND tipo=1);";
        sql = String.format(sql, c.getIdCuenta(), fechaString);
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_movimiento(rs));
        }
        return l;
    }
  
    
    public List<Movimiento> getMovementsBetweenDates(Cuenta account, String date_since, String date_until) throws SQLException, Exception{
        List<Movimiento> l = new ArrayList<>();
        String sql = "SELECT * FROM movimiento WHERE fecha BETWEEN '%s' and '%s' and ((cuentaOrigen=%d and tipo=1) or (cuentaDestino=%d and tipo=2));";
        sql = String.format(sql, date_since, date_until, account.getIdCuenta(), account.getIdCuenta());
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_movimiento(rs));
        }
        return l;
    }
    
    public List<Movimiento> getMovementsForInterestAccredit() throws SQLException, Exception {
        List<Movimiento> l = new ArrayList<>();
        Date today = new Date();
        String sql = "SELECT * FROM movimiento WHERE (solicitante='Banco Estatal' AND motivo='Intereses Ganados' AND tipo=2 AND month(fecha)=%d);";
        sql = String.format(sql, today.getMonth()+1);
        ResultSet rs = db.executeQuery(sql);
        while(rs.next()){
            l.add(render_movimiento(rs));
        }
        return l;
    }

    public void add(Movimiento p) throws Exception{
        String sql="INSERT INTO "
                + "movimiento(monto, fecha, motivo, tipo, cuentaOrigen, cuentaDestino, solicitante)"
                + " VALUES(%s,'%s','%s',%s,%s,%s,'%s')";
        
        Integer origen = null, destino = null;
        if(p.getCuentaOrigen() != null){ origen = p.getCuentaOrigen().getIdCuenta(); }
        if(p.getCuentaDestino() != null){ destino = p.getCuentaDestino().getIdCuenta(); }
        
        sql=String.format(sql,
                p.getMonto(),
                p.getFechaString(),
                p.getMotivo(),
                p.getTipo().getIdTipoMovimiento(),
                origen, destino, p.getSolicitante());        
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Movimiento ya existe");
        }
    }
    
    public void update(Movimiento p) throws Exception{
        String sql="UPDATE movimiento SET monto=%s, fecha='%s', motivo='%s', tipo=%s, "
                + "cuentaOrigen=%s, cuentaDestino=%s WHERE idVinculo=%s";
        
        Integer origen = null, destino = null;
        if(p.getCuentaOrigen() != null){ origen = p.getCuentaOrigen().getIdCuenta(); }
        if(p.getCuentaDestino() != null){ destino = p.getCuentaDestino().getIdCuenta(); }
        
        sql=String.format(sql,
                p.getMonto(),
                p.getFechaString(),
                p.getMotivo(),
                p.getTipo().getIdTipoMovimiento(),
                origen, destino);   
        if (db.executeUpdate(sql) == 0){
            throw new Exception("Movimiento no existe");
        }
    }

    private Movimiento render_movimiento(ResultSet rs) throws Exception{
        try {
            Movimiento m = new Movimiento();
            Calendar calendar = Calendar.getInstance();
            calendar.setTime(rs.getDate("fecha")); 
            calendar.add(Calendar.DATE, 1);//El mes inicia en 0, por ello + 1
            m.setFecha(calendar.getTime()); 
            m.setMonto(rs.getDouble("monto"));
            m.setMotivo(rs.getString("motivo"));
            m.setTipo(Dao_TipoMovimiento.instance().get(rs.getInt("tipo")));
            m.setSolicitante(rs.getString("solicitante"));
            m.setIdMovimiento(rs.getInt("idMovimiento"));
            Integer origen = rs.getInt("cuentaOrigen");
            Integer destino = rs.getInt("cuentaDestino");
            
            if(origen == 0){ m.setCuentaOrigen(null); }
            else{ m.setCuentaOrigen(Dao_Cuenta.instance().get(origen)); }
            
            if(destino == 0){ m.setCuentaDestino(null); }
            else{ m.setCuentaDestino(Dao_Cuenta.instance().get(destino)); }
            
            return m;
        } catch (SQLException ex) {
            return null;
        }
    }
    
    public void close(){}

}
