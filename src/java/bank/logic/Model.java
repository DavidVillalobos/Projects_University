package bank.logic;

import bank.data.Dao_Cliente;
import bank.data.Dao_Cuenta;
import bank.data.Dao_Moneda;
import bank.data.Dao_Movimiento;
import bank.data.Dao_TipoMovimiento;
import bank.data.Dao_Usuario;
import bank.data.Dao_Vinculo;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 *
 * @author Escinf
 */
public class Model {
    private static Model uniqueInstance;
    private final Dao_Usuario usuarios;
    private final Dao_Cliente clientes;
    private final Dao_Cuenta cuentas;
    private final Dao_Movimiento movimientos;
    private final Dao_Vinculo vinculos;
    private final Dao_Moneda monedas;
    private final Dao_TipoMovimiento tipomovimientos;
    
    public static Model instance(){
        if (uniqueInstance == null){
            uniqueInstance = new Model();
        }
        return uniqueInstance; 
    }

    private Model(){
        usuarios = Dao_Usuario.instance();
        clientes = Dao_Cliente.instance();
        cuentas = Dao_Cuenta.instance();
        movimientos = Dao_Movimiento.instance();
        vinculos = Dao_Vinculo.instance();
        monedas = Dao_Moneda.instance();
        tipomovimientos = Dao_TipoMovimiento.instance();
    }

    //----------------------Insertar datos-----------------------------//
    
    public void agregarVinculo(Cliente client, Cuenta cuenta) throws Exception{
        Vinculo link = new Vinculo();
        link.setCliente(client);
        link.setCuenta(cuenta);
        vinculos.add(link);
    }
    
    public void agregarCuenta(Cuenta c) throws Exception{
        cuentas.add(c);
    }
    
    public void agregarCliente(Cliente  c) throws Exception{
        Integer id = Integer.parseInt(usuarios.lastUser());
        id += 1;
        Usuario s = new Usuario();
        s.setIdUsuario(String.valueOf(id)); // tengo que cambiarlo a que sea como un AI
        s.setPassword(this.getPassword()); // cambiarlo a que autogenere una contraseña
        s.setTipo(false);
        usuarios.add(s);
        c.setUsuario(s);
        clientes.add(c);
    }
    
    public void agregarMovimiento(Movimiento move) throws Exception {
        movimientos.add(move);
    }
    
    //----------------------Busquedas-----------------------------//
    
    public Usuario usuarioFind(String cedula) throws Exception{
        Cliente client = clientes.get(cedula);
        if (client!=null){ return client.getUsuario(); }
        else throw new Exception("Usuario no existe");
    }

    public Cliente clienteFind(Usuario usuario) throws Exception{
        try{
            for(Cliente c: clientes.getAll()){
                if(c.getUsuario().getIdUsuario().equals(usuario.getIdUsuario())){
                    return c;
                }
            }
            return null;
        } catch (Exception ex) {
            throw new Exception("Ocurrio algun error");
        }
    }
    
    public Cliente clienteFind(String cedula) throws Exception{
        return clientes.get(cedula);
    }
    
    public Cuenta cuentaFind(Integer idCuenta) throws Exception{
        Cuenta result;
        try {
            result = cuentas.get(idCuenta);
            return result;
        } catch (Exception ex) {
            throw new Exception("Cuenta inexistente.");
        }
    }
    
    public List<Cuenta> cuentasFind(Cliente cliente) throws Exception{
        List<Cuenta> result = new ArrayList();
        for(Cuenta c: cuentas.getAll()){
            if(c.getCliente().getCedula().equals(cliente.getCedula())){
                result.add(c);
            }
        }
        return result;
    }
        
    public List<Cuenta> cuentasVinculadasFind(Cliente cliente) throws Exception{
        List<Cuenta> result = new ArrayList();
        for(Vinculo v: vinculos.getAll()){
            if(v.getCliente().getCedula().equals(cliente.getCedula())){
                result.add(v.getCuenta());
            }
        }
        return result;
    }
    
    public List<Movimiento> getRecentMovements(Cuenta cuenta) throws Exception{
        return movimientos.getRecentMovements(cuenta);
    }
    
    public List<Movimiento> getMovementsByDate(Cuenta cuenta, Date fecha)throws Exception {
        return movimientos.getMovementsByDate(cuenta, fecha);
    }
    
    public List<Moneda> getAllMonedas() throws SQLException{
        return monedas.getAll();
    }
    
    public Integer lastAccountId() throws SQLException{
        return cuentas.lastAccount();
    }
    
    public Tipomovimiento tipoMovimientoFind(int type) throws Exception {
        return tipomovimientos.get(type);
    }
    
    public Moneda monedaFindByName(String name) throws Exception{
        return monedas.getByName(name);
    }
    
    //----------------------Verificaciones-----------------------------//
    
    public Boolean cuentaVerify(Usuario s, Cuenta c) throws Exception{
        String s1_id, s2_id;
        s1_id = s.getIdUsuario(); 
        s2_id = c.getCliente().getUsuario().getIdUsuario();
        return s1_id.equals(s2_id);
    }
    
    //----------------------Actualizaciones-----------------------------//
    
    public void clienteUpdate(Cliente client) throws Exception {
        clientes.update(client);
    }
    
    public void usuarioUpdate(Usuario user) throws Exception {
        usuarios.update(user);
    }
    
    public void cuentaUpdate(Cuenta account) throws Exception {
        cuentas.update(account);
    }
        
    //--------------------------------------------
    
    private String getPassword() {
        String key = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        int length = 8;
        String pswd = "";
        for (int i = 0; i < length; i++) {
            pswd+=(key.charAt((int)(Math.random() * key.length())));
        }
        return pswd;
    }
}
