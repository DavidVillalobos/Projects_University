package bank.presentation.cashier.movements.deposit_withdrawal;

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
@WebServlet(name = "DepositWithdrawalController", urlPatterns = {"/presentation/cashier/movements/d_wd/show",
                                                                 "/presentation/cashier/movements/d_wd/search",
                                                                 "/presentation/cashier/movements/d_wd/movementShow",
                                                                 "/presentation/cashier/movements/d_wd/doMovement"})
public class Controller extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setAttribute("model", new Model());
        String viewUrl;
        switch(request.getServletPath()){
            case "/presentation/cashier/movements/d_wd/show": viewUrl = this.show(request); break;
            case "/presentation/cashier/movements/d_wd/search": viewUrl = this.search(request); break;
            case "/presentation/cashier/movements/d_wd/movementShow": viewUrl = this.movementShow(request); break;
            case "/presentation/cashier/movements/d_wd/doMovement": viewUrl = this.doMovement(request); break;
            default: viewUrl = ""; break;          
        }
        request.getRequestDispatcher(viewUrl).forward(request, response);
    }
    
    private String doMovement(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            model.setMonedas(domainModel.getAllMonedas());
        } catch (SQLException ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("Fatal-error", ex.getMessage());
            request.setAttribute("errors", errors);
            return "/presentation/Error.jsp";
        }
        Map<String, String> errors = this.completeData_M(request);
        if(errors.isEmpty()){
            this.updateData_M(request);
            return this.doMovementAction(request);
        }
        else{
            request.setAttribute("errors", errors);
            return "/presentation/cajero/movimientos/deposito_retiro/View.jsp";
        } 
        
    }
    
    private String doMovementAction(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        try {
            Usuario s = (Usuario) session.getAttribute("user");
            if (s.getTipo()) {
                model.setSelected(domainModel.cuentaFind(Integer.parseInt(model.getAccount_num())));
                double montoCuentaColones = model.getSelected().getSaldo()*model.getSelected().getMoneda().getValorColones();
                double montoMovemeColones = model.getMonto()*model.getMoneda().getValorColones();
                if(model.getTipoMovimiento() == 1){
                    if(montoMovemeColones > montoCuentaColones){
                        Map<String, String> errors = new HashMap<>();
                        errors.put("monto", "La cuenta no tiene suficiente saldo");
                        request.setAttribute("errors", errors);
                        return "/presentation/cajero/movimientos/deposito_retiro/View.jsp";
                    }    
                }
                domainModel.movementByCashier(model.getSelected(), 
                                              model.getMotivo(), 
                                              model.getNombre_solicitante(),
                                              model.getMonto(),
                                              model.getTipoMovimiento(),
                                              model.getMoneda());
                
                return "/presentation/cajero/movimientos/deposito_retiro/View_Detail.jsp";
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
    
    private Map<String,String> completeData_M(HttpServletRequest request){
        Map<String, String> errors = new HashMap<>();
        if(request.getParameter("monto").isEmpty()){
            errors.put("monto", "Es necesario un Monto.");
        }else{
            if(Double.parseDouble(request.getParameter("monto")) <= 0.0){
                errors.put("monto", "Es necesario un Monto Mayor a 0.");
            }
        }
        if(request.getParameter("moneda") == null){
            errors.put("moneda", "Moneda Necesaria");
        }else{
            if(request.getParameter("moneda").isEmpty()){
                errors.put("moneda", "Moneda Necesaria");
            }
        }
        if(request.getParameter("nombre").isEmpty()){
            errors.put("nombre", "Es necesario un Nombre.");
        }
        if(request.getParameter("motivo").isEmpty()){
            errors.put("motivo", "Es necesario un Motivo.");
        }
        if(request.getParameter("tipoMovimiento") == null){
            errors.put("tipoMovimiento", "Es necesario elegir un Movimiento.");
        }
        return errors;
    }
    
    private void updateData_M(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        model.setAccount_num(request.getParameter("cuenta"));
        model.setNombre_solicitante(request.getParameter("nombre"));
        model.setMonto(Double.parseDouble(request.getParameter("monto")));
        model.setMotivo(request.getParameter("motivo"));
        model.setNombre_solicitante(request.getParameter("nombre"));
        model.setTipoMovimiento(Integer.parseInt(request.getParameter("tipoMovimiento")));
        bank.logic.Model domainModel = bank.logic.Model.instance();
        String moneda = request.getParameter("moneda");
        try {
            model.setMoneda(domainModel.monedaFindByName(moneda));
        } catch (Exception ex) {
        }
    }
    
    private String movementShow(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            model.setMonedas(domainModel.getAllMonedas());
        } catch (SQLException ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("Fatal-error", ex.getMessage());
            request.setAttribute("errors", errors);
            return "/presentation/Error.jsp";
        }
        return this.movementShowAction(request);
    }
    
    private String movementShowAction(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        if(request.getParameter("idCuentafld")!= null){
            model.setAccount_num(request.getParameter("idCuentafld"));
        }else{ 
            Map<String, String> errors = new HashMap<>();
            errors.put("Fatal-error", "No hay numero de cuenta");
            request.setAttribute("errors", errors);
            return "/presentation/Error.jsp";
        }
        model.setMonto(0.0);
        model.setNombre_solicitante("");
        model.setMotivo("");
        return "/presentation/cajero/movimientos/deposito_retiro/View.jsp";
    }
    
    private String show(HttpServletRequest request) { 
        return this.showAction(request);
    }
    
    private String showAction(HttpServletRequest request){
        Model model= (Model) request.getAttribute("model");
        model.setId_cliente("");
        model.setAccount_num("");
        return "/presentation/cajero/movimientos/deposito_retiro/Account_Selection.jsp";
    }
    
    private String search(HttpServletRequest request) { 
        Map<String, String> errors = this.completeData(request);
        if(errors.isEmpty()){
            this.updateData(request);
            return "/presentation/cajero/movimientos/deposito_retiro/Account_Selection.jsp";
        }
        else{
            request.setAttribute("errors", errors);
            return "/presentation/cajero/movimientos/deposito_retiro/Account_Selection.jsp";
        }
    }
       
    private Map<String, String> completeData(HttpServletRequest request){
        Map<String, String> errors = new HashMap<>();
        if(request.getParameter("idAccount").isEmpty() && request.getParameter("id").isEmpty()){
            errors.put("id", "Es necesaria una Cedula o un numero de cuenta.");
            errors.put("idAccount", "Es necesaria una Cedula o un numero de cuenta.");
        }
        return errors;
    } 
    
    private void updateData(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        model.setAccount_num(request.getParameter("idAccount"));
        model.setId_cliente(request.getParameter("id"));
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            model.setAccounts(domainModel.cuentasFind(model.getAccount_num(), model.getId_cliente()));
        } catch (SQLException ex) {}  
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
