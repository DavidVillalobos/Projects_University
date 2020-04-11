package bank.presentation.client.transfers;

import bank.logic.Cliente;
import bank.logic.Cuenta;
import bank.logic.Movimiento;
import bank.logic.Tipomovimiento;
import bank.logic.Usuario;
import java.io.IOException;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
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
        try {
            Cuenta origen = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaOrigen")));
            Cuenta destino = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaDestino")));
            //Las cuentas siempre existen por que se muestran en un combobox
            model.setOrigin_account(origen);
            model.setDestination_account(destino);
            double monto = Double.parseDouble(request.getParameter("monto"));
            model.setMonto(monto);
            model.setMotivo(request.getParameter("motivo"));
            Map<String, String> errors = new HashMap<>();
            if(origen.getSaldo() < monto){
                errors.put("monto", "Saldo insuficiente en la cuenta de origen " + origen.getIdCuenta() + "\n El saldo actual es de " + origen.getSaldo());                
                model.setOrigin_account(null);
                model.setDestination_account(null);
            }else if(verifyLimitAccount(origen, monto)){
                errors.put("monto", "Monto excede el saldo limite de la cuenta " + origen.getIdCuenta() + "\n Para el dia de hoy. El limite es de " + origen.getLimite());
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
        bank.logic.Model domainModel = bank.logic.Model.instance();
        double total = monto;
        try {
            List<Movimiento> recentMovements = domainModel.getMovementsByDate(account, new Date());
            for (Movimiento move : recentMovements) {
                total += move.getMonto();
            }
            return account.getLimite() < total; //Se paso del limite?
        } catch (Exception ex) {}
        return false;
    }

    private Map<String, String> completeData(HttpServletRequest request) {
        Map<String, String> errors = new HashMap<>();
        if (request.getParameter("monto").isEmpty()) {
            errors.put("monto", "Debe ingresar un monto");
        }
        try{
            double monto = Double.parseDouble(request.getParameter("monto"));
            if(monto <= 0){  throw new Exception("Monto invalido"); }
        }catch(Exception ex){
            errors.put("monto", "El monto de la transferencia debe \n    ser numerico y mayor que 0");
        }
        if (request.getParameter("motivo").isEmpty()) {
            errors.put("motivo", "Debe ingresar un motivo");
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
        try {
            Cuenta origen = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaOrigen")));
            Cuenta destino = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaDestino")));
            //Las cuentas siempre existen por que se las muestra en un combobox
            model.setOrigin_account(origen);
            model.setDestination_account(destino);
            model.setMonto(Double.parseDouble(request.getParameter("monto")));
            model.setMotivo(request.getParameter("motivo"));
            if(checkTransfer(model)){
                if(retirement(request) && deposit(request)){
                    origen = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaOrigen")));
                    destino = domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaDestino")));  
                    model.setOrigin_account(origen);
                    model.setDestination_account(destino);
                    return "/presentation/cliente/transferencias/View_Detail.jsp";
                }
                return "/presentation/Error.jsp";
            }
            return "/presentation/client/accounts/show";
        } catch (Exception ex) {
            return "/presentation/Error.jsp";
        }
    }
    
    private boolean checkTransfer(Model model) throws Exception {
        bank.logic.Model domainModel = bank.logic.Model.instance();
        List<Movimiento> movements = domainModel.getMovementsByDate(model.getOrigin_account(), new Date());
        for (Movimiento move: movements) {
            if(move.equals(move)){ return false; }
        }
        return true;
    }
    
    private boolean retirement(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            Movimiento move = new Movimiento();
            move.setCuentaOrigen(model.getOrigin_account());
            move.setCuentaDestino(model.getDestination_account());
            move.setMonto(model.getMonto());
            move.setFecha(new Date());
            Tipomovimiento tp1;
            tp1 = domainModel.tipoMovimientoFind(1);
            move.setTipo(tp1);
            move.setMotivo(model.getMotivo());
            model.getOrigin_account().setSaldo(model.getOrigin_account().getSaldo() - model.getMonto());
            domainModel.cuentaUpdate(model.getOrigin_account());
            domainModel.agregarMovimiento(move);
        } catch (Exception ex) {
            return false;
        }
        return true;
    }
    
    private boolean deposit(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            double monto = model.getMonto();
            monto *= model.getOrigin_account().getMoneda().getValorColones();
            monto /= model.getDestination_account().getMoneda().getValorColones(); 
            Movimiento move = new Movimiento();
            move.setCuentaOrigen(model.getOrigin_account());
            move.setCuentaDestino(model.getDestination_account());
            move.setMonto(monto);
            Tipomovimiento tp2 = domainModel.tipoMovimientoFind(2);
            move.setTipo(tp2);
            move.setMotivo(model.getMotivo());
            move.setFecha(new Date());
            //Se debe actualizar la cuenta destino en caso de que se deposite a si mismo
            model.setDestination_account(domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaDestino"))));          
            model.getDestination_account().setSaldo(model.getDestination_account().getSaldo() + monto);
            domainModel.agregarMovimiento(move);
            domainModel.cuentaUpdate(model.getDestination_account());
        } catch (Exception ex) {
            return false;
        }
        return true;
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
