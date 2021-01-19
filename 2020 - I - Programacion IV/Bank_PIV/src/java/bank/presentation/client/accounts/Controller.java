package bank.presentation.client.accounts;

import bank.logic.Cliente;
import bank.logic.Usuario;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


@WebServlet(name = "ClientAccountsController", urlPatterns = {"/presentation/client/accounts/show"})
public class Controller extends HttpServlet {
    
    protected void processRequest(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException {
        request.setAttribute("model", new Model());        
        String viewUrl="";     
        switch (request.getServletPath()) {
            case "/presentation/client/accounts/show": viewUrl = this.show(request);
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
        } catch (Exception ex) {
            cliente=null;
        }
        try {        
            model.setAccounts(domainModel.cuentasFind(cliente));
            return "/presentation/cliente/cuentas/View.jsp";
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