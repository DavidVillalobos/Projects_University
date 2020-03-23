
/**
 *
 * @author David Villalobos
 */
/*
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

@WebServlet(name = "ClientDataController", urlPatterns = {"/presentation/client/data/show","/presentation/cliente/data/update"})
public class Controller extends HttpServlet {
    
    protected void processRequest(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException {
        request.setAttribute("model", new Model());        
        String viewUrl="";     
        switch (request.getServletPath()) {
            case "/presentation/client/data/show": viewUrl = this.show(request);
            break;
            case "/presentation/cliente/datos/update": viewUrl = this.update(request);
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
        Usuario user = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {
            cliente = domainModel.clienteFind(user);
            model.setCliente(cliente);
            return "/presentation/cliente/datos/View.jsp";
        } catch (Exception ex) {
            return "";
        }
    }
    
    private String update(HttpServletRequest request) { 
        try{
            Model model = (Model) request.getAttribute("model");
            HttpSession session = request.getSession(true);
            Usuario usuario = (Usuario) session.getAttribute("user");
            model.getCliente().setCedula(usuario.getIdUsuario());
            Map<String,String> errores =  this.validar(request);
            if(errores.isEmpty()){
                this.updateModel(request);          
                return this.updateAction(request);
            }
            else{
                request.setAttribute("errores", errores);
                return "/presentation/cliente/datos/View.jsp"; 
            }            
        }
        catch(Exception e){
            return "/presentation/Error.jsp";             
        }         
    }
    
    Map<String,String> validar(HttpServletRequest request){
        Map<String,String> errores = new HashMap<>();
        if (request.getParameter("nombreFld").isEmpty()){
            errores.put("nombreFld","Nombre requerido");
        }
        return errores;
    }
    
    void updateModel(HttpServletRequest request){
       bank.presentation.client.data.Model model= (bank.presentation.client.data.Model) request.getAttribute("model");     
        model.getCliente().setNombre(request.getParameter("nombreFld"));
   }

        
    public String updateAction(HttpServletRequest request) {
        bank.presentation.client.data.Model model= (bank.presentation.client.data.Model) request.getAttribute("model");
        bank.logic.Model  domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario usuario = (Usuario) session.getAttribute("usuario");
        model.getCliente().setCedula(usuario.getIdUsuario());
        model.getCliente().setUsuario(usuario);
        try {
            //domainModel.clienteUpdate(model.getCliente());
            return "/presentation/Index.jsp";
        } catch (Exception ex) {
            Map<String,String> errores = new HashMap<>();
            request.setAttribute("errores", errores);
            errores.put("nombreFld","cedula o nombre incorrectos");
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
    
}*/

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author David Villalobos
 */
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
        Usuario user = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {
            cliente = domainModel.clienteFind(user);
            model.setClient(cliente);
            return "/presentation/cliente/datos/View.jsp";
        } catch (Exception ex) {
            return "";
        }
    }
    
    private String update(HttpServletRequest request) { 
        Map<String,String> errores =  this.completeData(request);
        if(errores.isEmpty()){
            this.updateModel(request);          
            return this.updateAction(request);
        }
        else{
            request.setAttribute("errores", errores);
            return "/presentation/cliente/datos/View.jsp"; 
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
        if(request.getParameter("password").isEmpty()){
            errors.put("password", "Contraseña Necesaria");
        }
        return errors;
    } 
    
    void updateModel(HttpServletRequest request){
        bank.presentation.client.data.Model model = (bank.presentation.client.data.Model) request.getAttribute("model");    
        Cliente client = new Cliente();
        client.setUsuario(new Usuario());
        client.setNombre(request.getParameter("name"));
        client.setTelefono(Integer.getInteger(request.getParameter("telephone")));
        client.getUsuario().setIdUsuario(request.getParameter("user-name"));
        client.getUsuario().setPassword(request.getParameter("password"));
        model.setClient(client);
   }

        
    public String updateAction(HttpServletRequest request) {
        bank.presentation.client.data.Model model= (bank.presentation.client.data.Model) request.getAttribute("model");
        bank.logic.Model  domainModel = bank.logic.Model.instance();
        try {
            domainModel.clienteUpdate(model.getClient());
            return "/presentation/cliente/datos/view.jsp";
        } catch (Exception ex) {
            Map<String,String> errores = new HashMap<>();
            request.setAttribute("errores", errores);
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