
package bank.presentation.client.data;

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

@WebServlet(name = "ClientDataController", urlPatterns = {"/presentation/client/data/show","/presentation/client/data/update"})
public class Controller extends HttpServlet {
    
    protected void processRequest(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException {
        request.setAttribute("model", new Model());        
        String viewUrl="";     
        switch (request.getServletPath()) {
            case "/presentation/client/data/show": viewUrl = this.show(request);
            break;
            case "/presentation/client/data/update": viewUrl = this.update(request);
            break;
        }
        request.getRequestDispatcher(viewUrl).forward( request, response);
  }

    public String show(HttpServletRequest request) {
        return this.showAction(request);
    }
    
    public String showAction(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario usuario = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {
            cliente = domainModel.clienteFind(usuario);
        } catch (Exception ex) { cliente=null; }
        try {        
            model.setClient(cliente);
            return "/presentation/cliente/datos/View.jsp";
        } catch (Exception ex) { return ""; }
    }
    
    private String update(HttpServletRequest request) { 
        try{
            Model model = (Model) request.getAttribute("model");
            bank.logic.Model domainModel = bank.logic.Model.instance();
            HttpSession session = request.getSession(true);
            Usuario usuario = (Usuario) session.getAttribute("user");
            Map<String,String> errores =  this.completeData(request);
            model.setClient(domainModel.clienteFind(usuario));
            if(errores.isEmpty()){   
                this.updateModel(request);
                return this.updateAction(request);
            }
            else{
                request.setAttribute("errors", errores);
                return "/presentation/cliente/datos/View.jsp"; 
            }            
        }
        catch(Exception e){
            return "/presentation/Error.jsp";             
        }   
    }
    
    private Map<String, String> completeData(HttpServletRequest request){
        Map<String, String> errors = new HashMap<>();
        if(request.getParameter("name").isEmpty()){
            errors.put("name", "Nombre Necesario");
        }
        if(request.getParameter("telephone").isEmpty()){
            errors.put("telephone", "Telefono Necesario");
        }
        if(request.getParameter("user-name").isEmpty()){
            errors.put("user-name", "Usuario Necesario");
        }
        /*try {//check user-name not repeat
            HttpSession session = request.getSession(true);
            Usuario usuario = (Usuario) session.getAttribute("user");
            if(usuario != null && usuario.getIdUsuario() != usuario.getIdUsuario()){
                errors.put("user-name", "Usuario Ya Existe");
            }
        } catch (Exception ex) {}*/
        if(request.getParameter("password").isEmpty()){
            errors.put("password", "Contraseña Necesaria");
        }
        return errors;
    } 
    
    void updateModel(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");  
        Cliente client = model.getClient();
        client.setNombre(request.getParameter("name"));
        client.setTelefono(Integer.parseInt(request.getParameter("telephone")));
        client.getUsuario().setIdUsuario(request.getParameter("user-name"));
        client.getUsuario().setPassword(request.getParameter("password"));
    }

        
    public String updateAction(HttpServletRequest request) {
        Model model= (Model) request.getAttribute("model");
        bank.logic.Model  domainModel = bank.logic.Model.instance();
        try {
            domainModel.clienteUpdate(model.getClient());
            return "/presentation/cliente/datos/View.jsp";
        } catch (Exception ex) {
            Map<String,String> errores = new HashMap<>();
            request.setAttribute("errors", errores);
            errores.put("Error","Datos Incompletos");
            return "/presentation/cliente/datos/View.jsp"; 
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