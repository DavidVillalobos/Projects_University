/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bank.presentation.client.accountsLinked;

import bank.logic.Cliente;
import bank.logic.Cuenta;
import bank.logic.Usuario;
import java.io.IOException;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
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
@WebServlet(name = "ClientAccountsLinkedController", urlPatterns = {"/presentation/client/accountsLinked/show", "/presentation/client/accountsLinked/link", "/presentation/client/accountsLinked/search"})
public class Controller extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("model", new Model());
        String viewUrl = "";
        switch (request.getServletPath()) {
            case "/presentation/client/accountsLinked/show":
                viewUrl = this.show(request);
                break;
            case "/presentation/client/accountsLinked/link":
                viewUrl = this.link(request);
                break;
            case "/presentation/client/accountsLinked/search":
                viewUrl = this.search(request);
                break;
        }
        request.getRequestDispatcher(viewUrl).forward(request, response);
    }

    public String show(HttpServletRequest request) {
        return this.showAction(request);
    }

    public String link(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario user = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {
            cliente = domainModel.clienteFind(user);
            model.setAccountsLinked(domainModel.cuentasVinculadasFind(cliente));
            return this.linkAction(request);
        } catch (Exception ex) {
            return "";
        }
    }

    public String search(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario user = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {
            cliente = domainModel.clienteFind(user);
            model.setAccountsLinked(domainModel.cuentasVinculadasFind(cliente));
            Map<String, String> errores = this.completeData(request);
            if (errores.isEmpty()) {
                return this.searchAction(request);
            } else {
                request.setAttribute("errors", errores);
                return "/presentation/cliente/cuentasVinculadas/View.jsp";
            }
        } catch (Exception ex) {
            return "";
        }
    }

    public String showAction(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario user = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {
            cliente = domainModel.clienteFind(user);
            model.setAccountsLinked(domainModel.cuentasVinculadasFind(cliente));
            return "/presentation/cliente/cuentasVinculadas/View.jsp";
        } catch (Exception ex) {
            return "";
        }
    }

    public String linkAction(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario user = (Usuario) session.getAttribute("user");
        Cliente cliente;
        Cuenta accountToLink;
        Map<String, String> errores = this.completeData(request);
        try {
            if (errores.isEmpty()) {
                accountToLink = domainModel.cuentaFind(Integer.parseInt(request.getParameter("idAccount").replace(" ", "")));
                model.setAccountToLink(accountToLink);
                cliente = domainModel.clienteFind(user);
                errores = this.checkLinkAccount(cliente, accountToLink);
                if (errores.isEmpty()) {
                    domainModel.agregarVinculo(cliente, model.getAccountToLink());
                    model.setAccountsLinked(domainModel.cuentasVinculadasFind(cliente));
                    return "/presentation/cliente/cuentasVinculadas/View.jsp";
                }else{
                    request.setAttribute("errors", errores);
                    return "/presentation/cliente/cuentasVinculadas/View.jsp";
                }
            } else {
                request.setAttribute("errors", errores);
                return "/presentation/cliente/cuentasVinculadas/View.jsp";
            }
        } catch (Exception ex) {
            return "";
        }
    }

    public String searchAction(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        Cuenta accountToLink;
        try {
            accountToLink = domainModel.cuentaFind(Integer.parseInt(request.getParameter("idAccount").replace(" ", "")));
            model.setAccountToLink(accountToLink);
            return "/presentation/cliente/cuentasVinculadas/View.jsp";
        } catch (Exception ex) {
            Map<String, String> errors = new HashMap<>();
            errors.put("idAccount", "Cuenta no existe");
            request.setAttribute("errors", errors);
            return "/presentation/cliente/cuentasVinculadas/View.jsp";
        }
    }

    private Map<String, String> completeData(HttpServletRequest request) {
        Map<String, String> errors = new HashMap<>();
        if (request.getParameter("idAccount").isEmpty()) {
            errors.put("idAccount", "Numero de Cuenta Necesario");
        }
        return errors;
    }
    
    private Map<String, String> checkLinkAccount(Cliente cliente, Cuenta account) throws Exception {
        Map<String, String> errors = new HashMap<>();
        bank.logic.Model domainModel = bank.logic.Model.instance();
        List<Cuenta> cuentas = domainModel.cuentasVinculadasFind(cliente);
        for (Cuenta c: cuentas) {
            if(Objects.equals(c.getIdCuenta(), account.getIdCuenta())){
                errors.put("idAccount", "Cuenta ya fue vinculada");
            }
        }
        return errors;
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
