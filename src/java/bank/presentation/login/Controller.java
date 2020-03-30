package bank.presentation.login;

import bank.logic.Cliente;
import bank.logic.Usuario;
import java.io.IOException;
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
@WebServlet(name = "LoginController", urlPatterns = {"/presentation/login/show", "/presentation/login/login", 
                                                     "/presentation/logout/show"})
public class Controller extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setAttribute("model", new Model());
        String viewUrl;
        switch(request.getServletPath()){
            case "/presentation/login/show": viewUrl = this.show(request); break;
            case "/presentation/login/login": viewUrl = this.login(request); break;
            case "/presentation/logout/show": viewUrl = this.logout(request); break;
            default: viewUrl = ""; break;          
        }
        request.getRequestDispatcher(viewUrl).forward(request, response);
    }
    
    private String show(HttpServletRequest request){
        return this.showAction(request);
    }
    
    private String showAction(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        model.getClient().setCedula("");
        model.getClient().getUsuario().setPassword("");
        return "/presentation/login/View.jsp";
    }
    
    private String login(HttpServletRequest request) { 
        Map<String, String> errors = this.completeData(request);
        if(errors.isEmpty()){
            this.updateData(request);
            return this.loginAction(request);
        }
        else{
            request.setAttribute("errors", errors);
            return "/presentation/login/View.jsp";
        }        
    }
       
    private Map<String, String> completeData(HttpServletRequest request){
        Map<String, String> errors = new HashMap<>();
        if(request.getParameter("cedula").isEmpty()){
            errors.put("cedula", "Cedula Necesaria");
        }
        if(request.getParameter("password").isEmpty()){
            errors.put("password", "Contraseña Necesaria");
        }
        return errors;
    } 
    
    private void updateData(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        model.getClient().setCedula(request.getParameter("cedula"));
        model.getClient().getUsuario().setPassword(request.getParameter("password"));
    }
    
    private String loginAction(HttpServletRequest request) {
        Model model= (Model) request.getAttribute("model");
        HttpSession session = request.getSession(true);
        try {
            Usuario db_user = this.validateCredentials(model.getClient());
            session.setAttribute("user", db_user);
            if (db_user.getTipo()) {
                return "/presentation/cashier/accounts/search/show";
            } else {
                return "/presentation/client/accounts/show";
            }
        } catch (Exception ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("cedula", "Cedula o Contraseña Erronea");
            errors.put("password", "Cedula o Contraseña Erronea");
            request.setAttribute("errors", errors);
            return "/presentation/login/View.jsp"; 
        }
    }
    
    private Usuario validateCredentials(Cliente client) throws Exception{
        Usuario db_user;
        try {
            String x = client.getCedula();
            db_user = bank.logic.Model.instance().usuarioFind(x);
            if(!db_user.getPassword().equals(client.getUsuario().getPassword())){
                throw new Exception();
            }
        }catch (Exception ex) {
            throw new Exception("Usuario o Contraseña Erroneos");
        }
        return db_user;
    }

    private String logout(HttpServletRequest request){
        return this.logoutAction(request);
    }

    private String logoutAction(HttpServletRequest request){
        HttpSession session = request.getSession(true);
        session.removeAttribute("user");
        session.invalidate();
        return "/presentation/Index.jsp";   
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