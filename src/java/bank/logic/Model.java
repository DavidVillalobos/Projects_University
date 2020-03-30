package bank.logic;

import bank.data.Dao_Cliente;
import bank.data.Dao_Cuenta;
import bank.data.Dao_Movimiento;
import bank.data.Dao_Usuario;
import bank.data.Dao_Vinculo;
import java.util.ArrayList;
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
        
    }

    //----------------------Insertar datos-----------------------------//
    
    public void agregarVinculo(Cliente client, Cuenta cuenta) throws Exception{
        Vinculo link = new Vinculo();
        link.setCliente(client);
        link.setCuenta(cuenta);
        vinculos.add(link);
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

}
