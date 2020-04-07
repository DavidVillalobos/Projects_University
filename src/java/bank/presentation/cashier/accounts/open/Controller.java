package bank.presentation.cashier.accounts.open;

import bank.logic.Cliente;
import bank.logic.Moneda;
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
@WebServlet(name = "CashierOpenAccountController", urlPatterns = {"/presentation/cashier/accounts/open/show", 
                                                                   "/presentation/cashier/accounts/open/create"})
public class Controller extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setAttribute("model", new Model());
        String viewUrl;
        switch(request.getServletPath()){
            case "/presentation/cashier/accounts/open/show": viewUrl = this.show(request); break;
            case "/presentation/cashier/accounts/open/create": viewUrl = this.create(request); break;
            default: viewUrl = ""; break;          
        }
        request.getRequestDispatcher(viewUrl).forward(request, response);
    }
    
    private String show(HttpServletRequest request) { 
        return this.showAction(request);
    }
    
    private String showAction(HttpServletRequest request){
        Model model= (Model) request.getAttribute("model");
        bank.logic.Model domainModel =  bank.logic.Model.instance();
        model.getClient().setCedula("");
        model.getClient().setNombre("");
        model.getClient().setTelefono(0);
        model.getAccount().setMoneda(null);
        model.getAccount().setLimite(0.0);
        try {
            model.setMonedas(domainModel.getAllMonedas());
        } catch (SQLException ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("Fatal-error", ex.getMessage());
            request.setAttribute("errors", errors);
            return "/presentation/Error.jsp";
        }
        return "/presentation/cajero/cuentas/abrir/View.jsp";
    }
    
    private String create(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        try {
            model.setMonedas(bank.logic.Model.instance().getAllMonedas());
        } catch (SQLException ex) {
        }
        Map<String, String> errors = this.completeData(request);
        if(errors.isEmpty()){
            this.updateData(request);
            return this.createAction(request);
        }
        else{
            request.setAttribute("errors", errors);
            return "/presentation/cajero/cuentas/abrir/View.jsp";
        }        
    }
    
    private String createAction(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        try {
            Usuario s = (Usuario) session.getAttribute("user");
            if (s.getTipo()) {
                Cliente client;
                if(model.getRegistrated()){
                    try{
                        client = domainModel.clienteFind(model.getClient().getCedula());
                    }catch(Exception ex){ 
                        model.setRegistrated(false);
                        model.getClient().setNombre("");
                        model.getClient().setTelefono(0);
                        request.setAttribute("added", false);
                        return "/presentation/cajero/cuentas/abrir/View.jsp";
                    }
                    model.setClient(client);
                    model.getAccount().setCliente(client);
                    domainModel.agregarCuenta(model.getAccount());
                    domainModel.agregarVinculo(client, model.getAccount());
                    request.setAttribute("added", true);
                }
                else{
                    client = model.getClient();
                    domainModel.agregarCliente(client);
                    model.setRegistrated(true);
                    client = domainModel.clienteFind(model.getClient().getCedula());
                    model.getAccount().setCliente(client);
                    domainModel.agregarCuenta(model.getAccount());
                    model.getAccount().setIdCuenta(domainModel.lastAccountId());
                    domainModel.agregarVinculo(client, model.getAccount());
                    request.setAttribute("added", true);
                }
                
                return "/presentation/cajero/cuentas/abrir/View.jsp";
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
       
    private Map<String, String> completeData(HttpServletRequest request){
        Map<String, String> errors = new HashMap<>();
        if(request.getParameter("cedula").isEmpty()){
            errors.put("cedula", "Cedula Necesaria");
        }
        if(request.getParameter("limite").isEmpty()){
            errors.put("limite", "Limite Necesario");
        }
        if(request.getParameter("moneda") == null){
            errors.put("moneda", "Moneda Necesaria");
        }else{
            if(request.getParameter("moneda").isEmpty()){
                errors.put("moneda", "Moneda Necesaria");
            }
        }
        if(request.getParameter("nombre") != null){
            Model model = (Model) request.getAttribute("model");
            model.setRegistrated(false);
            if(request.getParameter("nombre").isEmpty()){
                errors.put("nombre", "Nombre Necesario");
            }
            if(request.getParameter("telefono").isEmpty()){
                errors.put("telefono", "Telefono Necesario");
            }
        }
        return errors;
    } 
    
    private void updateData(HttpServletRequest request){
        Model model = (Model) request.getAttribute("model");
        String cedula = request.getParameter("cedula");
        Double limite = Double.valueOf(request.getParameter("limite"));
        String moneda = request.getParameter("moneda");
        if(!model.getRegistrated()){
            Integer telefono = Integer.parseInt(request.getParameter("telefono"));
            String nombre = request.getParameter("nombre");
            model.getClient().setNombre(nombre);
            model.getClient().setTelefono(telefono);
        }
        model.getAccount().setMoneda(new Moneda(moneda));
        model.getAccount().setSaldo(0);
        model.getClient().setCedula(cedula);
        model.getAccount().setLimite(limite);
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
