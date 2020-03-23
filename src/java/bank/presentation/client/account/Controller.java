package bank.presentation.client.account;

import bank.logic.Cuenta;
import bank.logic.Movimiento;
import bank.logic.Usuario;
import java.io.IOException;
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
 * @author Kevin Flores
 */
@WebServlet(name = "ClientAccountController", urlPatterns = {"/presentation/client/account/show"})
public class Controller extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setAttribute("model", new Model());        
        String viewUrl="";     
        switch (request.getServletPath()) {
            case "/presentation/client/account/show": viewUrl = this.show(request);
            break;
        }          
        request.getRequestDispatcher(viewUrl).forward( request, response); 
    }
    
    private String show(HttpServletRequest request) { 
        Map<String, String> errors = this.completeData(request);
        if(errors.isEmpty()){
            this.updateData(request);
            return this.showAction(request);
        }
        else{
            request.setAttribute("errors", errors);
            return "/presentation/Error.jsp";
        }        
    }
    
    private String showAction(HttpServletRequest request){
        Model model= (Model) request.getAttribute("model");
        HttpSession session = request.getSession(true);
        try {
            Cuenta db_account = this.validateCredentials(model.getAccount());
            List<Movimiento> db_movements = bank.logic.Model.instance().getRecentMovements(db_account);
            Usuario s = (Usuario) session.getAttribute("user");
            if (bank.logic.Model.instance().cuentaVerify(s, db_account)) {   
                model.setAccount(db_account);
                model.setMovements(db_movements);
                return "/presentation/cliente/cuenta/View.jsp";
            } else {
                throw new Exception("Usuario incompatible con la Cuenta.");
            }
        } catch (Exception ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("Fatal-error", ex.getMessage());
            request.setAttribute("errors", errors);
            return "/presentation/Error.jsp"; 
        }
    }
       
    private Map<String, String> completeData(HttpServletRequest request){
        Map<String, String> errors = new HashMap<>();
        if(request.getParameter("idCuentafld").isEmpty()){
            errors.put("idCuentafld", "Numero de Cuenta Necesario");
        }
        return errors;
    } 
    
    private void updateData(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        Integer num_account = Integer.parseInt(request.getParameter("idCuentafld"));
        model.getAccount().setIdCuenta(num_account);
    }
    
    private Cuenta validateCredentials(Cuenta c) throws Exception{
        Cuenta db_account;
        try {
            Integer x = c.getIdCuenta();
            db_account = bank.logic.Model.instance().cuentaFind(x);
            return db_account;
        }catch (Exception ex) {
            throw new Exception(ex.getMessage());
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
