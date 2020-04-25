package bank.presentation.cashier.movements.transfer;

import bank.logic.Usuario;
import java.io.IOException;
import java.sql.SQLException;
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
 * @author Kevin Flores
 */
@WebServlet(name = "CashierTranferController", urlPatterns = {"/presentation/cashier/movements/transfer/show",
"/presentation/cashier/movements/transfer/searchOrigin","/presentation/cashier/movements/transfer/searchDestiny",
"/presentation/cashier/movements/transfer/processTransfer"})
public class Controller extends HttpServlet {
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setAttribute("model", new Model());
        String viewUrl;
        switch(request.getServletPath()){
            case "/presentation/cashier/movements/transfer/show": viewUrl = this.show(request); break;
            case "/presentation/cashier/movements/transfer/searchOrigin": viewUrl = this.search(request, 1); break;
            case "/presentation/cashier/movements/transfer/searchDestiny": viewUrl = this.search(request, 2); break;
            case "/presentation/cashier/movements/transfer/processTransfer": viewUrl = this.processTransfer(request); break;
            default: viewUrl = ""; break;          
        }
        request.getRequestDispatcher(viewUrl).forward(request, response);
    }
    private String processTransfer(HttpServletRequest request) {
        Map<String, String> errors = completeData(request, 3);
        this.updateData(request, 3);
         try {
            if(errors.isEmpty()){
                return this.processTransferAction(request);
            }else{
                request.setAttribute("errors", errors);
                return "/presentation/cajero/movimientos/transferencia/View.jsp";
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
        try {
            Usuario s = (Usuario) session.getAttribute("user");
            if (s.getTipo()) {
                double montoColonesOrigen = model.getOrigin_account().getSaldo();
                double montoMovemeColones = model.getMonto();
                if(montoMovemeColones > montoColonesOrigen){
                    Map<String, String> errors = new HashMap<>();
                    errors.put("monto", "La Cuenta Origen no tiene suficiente saldo");
                    request.setAttribute("errors", errors);
                    return "/presentation/cajero/movimientos/transferencia/View.jsp";
                }    
                domainModel.movementByCashier(model.getOrigin_account(), 
                                              model.getMotivo(), 
                                              model.getOrigin_account().getCliente().getNombre(),
                                              model.getMonto(),
                                              1,
                                              model.getOrigin_account().getMoneda());
                
                domainModel.movementByCashier(model.getDestination_account(), 
                                              model.getMotivo(), 
                                              model.getOrigin_account().getCliente().getNombre(),
                                              model.getMonto(),
                                              2,
                                              model.getOrigin_account().getMoneda());
                
                return "/presentation/cajero/movimientos/transferencia/View_Detail.jsp";
            } else {
                throw new Exception("Acceso invalido (No es Cajero).");
            }
        } catch (Exception ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("Fatal-error", ex.getMessage());
            request.setAttribute("errors", errors);
            return "/presentation/Error.jsp"; 
        }
    }
    
    private String search(HttpServletRequest request, int type) { 
        Map<String, String> errors = this.completeData(request, type);
        this.updateData(request, type);
        if(errors.isEmpty()){
            return "/presentation/cajero/movimientos/transferencia/View.jsp";
        }
        else{
            request.setAttribute("errors", errors);
            return "/presentation/cajero/movimientos/transferencia/View.jsp";
        }
    }
       
    private Map<String, String> completeData(HttpServletRequest request, int type){
        Map<String, String> errors = new HashMap<>();
        switch(type){
            case 1:{
                if(request.getParameter("n_account_1").isEmpty() && request.getParameter("id_1").isEmpty()){
                    errors.put("id_1", "Es necesaria una Cédula o un Número de cuenta.");
                    errors.put("n_account_1", "Es necesaria una Cédula o un Número de cuenta.");
                }
                break;
            }
            case 2:{
                if(request.getParameter("n_account_2").isEmpty() && request.getParameter("id_2").isEmpty()){
                    errors.put("id_2", "Es necesaria una Cédula o un Número de cuenta.");
                    errors.put("n_account_2", "Es necesaria una Cédula o un Número de cuenta.");
                }
                break;
            }
            case 3:{
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
                if (request.getParameter("cuentaOrigen") == null){ 
                    errors.put("cuentaOrigen", "Cuenta de Origen necesaria");
                }
                if(request.getParameter("cuentaDestino") == null) {
                    errors.put("cuentaDestino", "Cuenta de Destino necesaria");
                }
            }
        }
        return errors;
    } 
    
    private void updateData(HttpServletRequest request, int type){
        Model model = (Model) request.getAttribute("model");
        model.setId_1(request.getParameter("id_1"));
        model.setId_2(request.getParameter("id_2"));
        model.setN_account_1(request.getParameter("n_account_1"));
        model.setN_account_2(request.getParameter("n_account_2"));
        model.setMonto(Double.parseDouble(request.getParameter("monto")));
        model.setMotivo(request.getParameter("motivo"));
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            model.setOrigin_accounts(domainModel.cuentasFind(model.getN_account_1(), model.getId_1()));
            model.setDestination_accounts(domainModel.cuentasFind(model.getN_account_2(), model.getId_2()));
        } catch (SQLException ex) {
        }
        if(request.getParameter("cuentaDestino") != null){
            try {
                model.setDestination_account(domainModel.cuentaFind(Integer.parseInt(request.getParameter("cuentaDestino"))));
            } catch (Exception ex) {
                model.setDestination_account(null);
            }
        }
        if(request.getParameter("cuentaOrigen") != null){
            try {
                Integer x = Integer.parseInt(request.getParameter("cuentaOrigen"));
                model.setOrigin_account(domainModel.cuentaFind(x));
            } catch (Exception ex) {
                model.setOrigin_account(null);
            }
        }
        switch(type){
            case 1: model.setOrigin_account(null); break;
            case 2: model.setDestination_account(null); break;
            default: break;
        }
    }
    
    private String show(HttpServletRequest request) {
        return this.showAction(request);
    }

    private String showAction(HttpServletRequest request) {
        return "/presentation/cajero/movimientos/transferencia/View.jsp";
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
