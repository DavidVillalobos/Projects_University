package bank.presentation.cashier.accounts.interests;

import bank.logic.Cuenta;
import bank.logic.Movimiento;
import bank.logic.Tipomovimiento;
import java.io.IOException;
import java.sql.SQLException;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
/**
 *
 * @author David Villalobos
 */
@WebServlet(name = "CashierAccountInterestController", urlPatterns = {"/presentation/cashier/accounts/interests/show",
                                                                        "/presentation/cashier/accounts/interests/accredit"})
public class Controller extends HttpServlet {
    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setAttribute("model", new Model());
        String viewUrl;
        switch(request.getServletPath()){
            case "/presentation/cashier/accounts/interests/show": viewUrl = this.show(request); break;
            case "/presentation/cashier/accounts/interests/accredit": viewUrl = this.accredit(request); break;
            default: viewUrl = ""; break;          
        }
        request.getRequestDispatcher(viewUrl).forward(request, response);
    }
    
    private String show(HttpServletRequest request) { 
        return this.showAction(request);
    }
    
    private String showAction(HttpServletRequest request){
        bank.logic.Model domainModel = bank.logic.Model.instance();
        Model model = (Model) request.getAttribute("model");
        try {
            model.setMonedas(domainModel.getAllMonedas());
            return "/presentation/cajero/cuentas/intereses/View.jsp";
        } catch (SQLException ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("Fatal-error", ex.getMessage());
            request.setAttribute("errors", errors);
            return "/presentation/Error.jsp"; 
        }
        
    }
    
    private String accredit(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        if(!accreditProcessDone(request)){
            return this.accreditAction(request);
        }
        try {
            model.setAcreditas(domainModel.getMovementsForInterestAccredit());
            return "/presentation/cajero/cuentas/intereses/View_Detail.jsp";
        } catch (Exception ex) {}
        return "/presentation/Error.jsp"; 
    }
    
    private String accreditAction(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            List<Cuenta> cuentas = domainModel.getAllCuentas();
            for(Cuenta c : cuentas){
                accreditInterest(c);
            }
            model.setAcreditas(domainModel.getMovementsForInterestAccredit());
            return "/presentation/cajero/cuentas/intereses/View_Detail.jsp";
        } catch (Exception ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("Fatal-error", ex.getMessage());
            request.setAttribute("errors", errors);
        }
        return "/presentation/Error.jsp";
    }
    
    private void accreditInterest(Cuenta c){
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            if(0 < c.getSaldo()){
                double monto = c.getSaldo() * (c.getMoneda().getInteres()/100);
                Movimiento deposit = new Movimiento();
                deposit.setMonto(monto);
                deposit.setSolicitante("Banco Estatal");
                Tipomovimiento tp2 = domainModel.tipoMovimientoFind(2);
                deposit.setTipo(tp2);
                deposit.setMotivo("Intereses Ganados");
                deposit.setFecha(new Date());
                deposit.setCuentaDestino(c);
                domainModel.agregarMovimiento(deposit);
                c.setSaldo( c.getSaldo() + monto);
                domainModel.cuentaUpdate(c);
            }
        } catch (Exception ex) {}
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

    private boolean accreditProcessDone(HttpServletRequest request) {
        bank.logic.Model domainModel = bank.logic.Model.instance();
        try {
            if(domainModel.getMovementsForInterestAccredit().isEmpty()){
                return false;
            }
            return true;
        } catch (Exception ex) {}
        return false;
    }
}
