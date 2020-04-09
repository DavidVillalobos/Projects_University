package bank.presentation.client.transfers;

import bank.logic.Cliente;
import bank.logic.Cuenta;
import bank.logic.Movimiento;
import bank.logic.Tipomovimiento;
import bank.logic.Usuario;
import java.io.IOException;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 *
 * @author David Villalobos
 */
@WebServlet(name = "TransfersController", urlPatterns = {"/presentation/client/transfers/show",
"/presentation/client/transfers/processTransfer", "/presentation/client/transfers/transfer"})
public class Controller extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setAttribute("model", new Model());
        String viewUrl;
        switch (request.getServletPath()) {
            case "/presentation/client/transfers/show":
                viewUrl = this.show(request);
                break;
            case "/presentation/client/transfers/processTransfer":
                viewUrl = this.processTransfer(request);
                break;
            case "/presentation/client/transfers/transfer":
                viewUrl = this.transfer(request);
                break;
            default:
                viewUrl = "";
                break;
        }
        request.getRequestDispatcher(viewUrl).forward(request, response);
    }

    private String show(HttpServletRequest request) {
        return this.showAction(request);
    }

    private String showAction(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario usuario = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {
            cliente = domainModel.clienteFind(usuario);
            model.setOrigin_accounts(domainModel.cuentasFind(cliente));
            model.setDestination_accounts(domainModel.cuentasVinculadasFind(cliente));
            return "/presentation/cliente/transferencias/View.jsp";
        } catch (Exception ex) {
            return "";
        }
    }
    
    private String processTransfer(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        Map<String, String> errors = completeData(request);
         HttpSession session = request.getSession(true);
        Usuario usuario = (Usuario) session.getAttribute("user");
        Cliente cliente;
         try {
            cliente = domainModel.clienteFind(usuario);
            model.setOrigin_accounts(domainModel.cuentasFind(cliente));
            model.setDestination_accounts(domainModel.cuentasVinculadasFind(cliente));
            if(errors.isEmpty()){
                return this.processTransferAction(request);
            }else{
                request.setAttribute("errors", errors);
                return "/presentation/cliente/transferencias/View.jsp";
            }
         } catch (Exception ex) {
            return "";
        }
    }
    
    //HashMap parametros = (HashMap) request.getParameterMap();//ver todos los parametros
    private String processTransferAction(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario usuario = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {// working . . . here
            cliente = domainModel.clienteFind(usuario);
            Cuenta origen = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaOrigen")));
            Cuenta destino = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaDestino")));
            //Las cuentas siempre existen por que se muestran en un combobox
            model.setOrigin_account(origen);
            model.setDestination_account(destino);
            double monto = Double.parseDouble(request.getParameter("monto"));
            model.setMonto(monto);
            Map<String, String> errors = new HashMap<>();
            if(origen.getSaldo() < monto){
                errors.put("monto", "Saldo insuficiente en la cuenta de origen " + origen.getIdCuenta() + "\n El saldo actual es de " + origen.getSaldo());                
                model.setOrigin_account(null);
                model.setDestination_account(null);
            }else if(verifyLimitAccount(origen, monto)){
                errors.put("monto", "Monto excede el saldo limite de la cuenta " + origen.getIdCuenta() + "\n El limite es de " + origen.getLimite());
                model.setOrigin_account(null);
                model.setDestination_account(null);
            }
            request.setAttribute("errors", errors);
            return "/presentation/cliente/transferencias/View.jsp";
        } catch (Exception ex) {
            return "";
        }
    }
    
    private boolean verifyLimitAccount(Cuenta account, double monto){
        double total = monto;
        //Agregar a total el monto de todos los movimientos realizados hoy
        return account.getLimite() < total; //Se paso del limite?
    }

    private Map<String, String> completeData(HttpServletRequest request) {
        Map<String, String> errors = new HashMap<>();
        if (request.getParameter("monto").isEmpty()) {
            errors.put("monto", "Debe ingresar un monto");
        }
        if (request.getParameter("cuentaOrigen") == null || request.getParameter("cuentaDestino") == null) {
            errors.put("cuentaDestino", "Cuenta de Destino necesaria");
            errors.put("cuentaOrigen", "Cuenta de Origen necesaria");
        }
        return errors;
    }
    
    private String transfer(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        Date today = new Date(); 
        try {
            //Colocar los datos en el Model
            Cuenta origen = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaOrigen")));
            Cuenta destino = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaDestino")));
            //Las cuentas siempre existen por que se las muestra en un combobox
            model.setOrigin_account(origen);
            model.setDestination_account(destino);  
            //Obtener el monto
            double monto = Double.parseDouble(request.getParameter("monto"));
            model.setMonto(monto);
            
            //Ingresar el primer movimiento retiro
            Movimiento m1 = new Movimiento();
            m1.setCuentaOrigen(origen);
            m1.setCuentaDestino(destino);
            m1.setMonto(monto);
            m1.setFecha(today);
            //Buscamos el tipo de movimiento retiro
            Tipomovimiento tp1 = domainModel.tipoMovimientoFind(1);
            m1.setTipo(tp1);
            m1.setMotivo(tp1.getNombre()); //Esto se pregunta al usuario
           
            //Realizamos la conversion del monto
            monto *= origen.getMoneda().getValorColones();
            monto /= destino.getMoneda().getValorColones();
            
            //Ingresar el segundo movimiento deposito
            Movimiento m2 = new Movimiento();
            m2.setCuentaOrigen(origen);
            m2.setCuentaDestino(destino);
            m2.setMonto(monto);
            //Buscamos el tipo de movimiento deposito
            Tipomovimiento tp2 = domainModel.tipoMovimientoFind(2);
            m2.setTipo(tp2);
            m2.setMotivo(tp2.getNombre()); //Esto se pregunta al usuario
            m2.setFecha(today);
            //Realizamos el retiro
            origen.setSaldo(origen.getSaldo() - monto);
            domainModel.agregarMovimiento(m1); //Se registra el movimiento
            //Realizamos el deposito
            destino.setSaldo(destino.getSaldo() + monto);
            domainModel.agregarMovimiento(m2); //Se registra el movimiento
            
            //Actualizamos las cuentas
            domainModel.cuentaUpdate(origen);
            domainModel.cuentaUpdate(destino);

            
            return "/presentation/cliente/transferencias/View.jsp";
        } catch (Exception ex) {
            return "";
        }
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    public String getServletInfo() {
        return "Short description";
    }

}
