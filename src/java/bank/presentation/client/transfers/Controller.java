package bank.presentation.client.transfers;

import bank.logic.Cliente;
import bank.logic.Cuenta;
import bank.logic.Usuario;
import java.io.IOException;
import java.util.HashMap;
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
@WebServlet(name = "TransfersController", urlPatterns = {"/presentation/client/transfers/show",
"/presentation/client/transfers/processTransfer", "/presentation/client/transfers/transfer"})
public class Controller extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setAttribute("model", new Model());
        String viewUrl;
        switch (request.getServletPath()) {
            case "/presentation/client/transfers/show":
                viewUrl = this.show(request);
                break;
            case "/presentation/client/transfers/processTransfer":
                viewUrl = this.processTransfer(request);
                break;
            case "/presentation/client/transfers/transfer":
                viewUrl = this.transfer(request);
                break;
            default:
                viewUrl = "";
                break;
        }
        request.getRequestDispatcher(viewUrl).forward(request, response);
    }

    private String show(HttpServletRequest request) {
        return this.showAction(request);
    }

    private String showAction(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario usuario = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {
            cliente = domainModel.clienteFind(usuario);
            model.setOrigin_accounts(domainModel.cuentasFind(cliente));
            model.setDestination_accounts(domainModel.cuentasVinculadasFind(cliente));
            return "/presentation/cliente/transferencias/View.jsp";
        } catch (Exception ex) {
            return "";
        }
    }
    
    private String processTransfer(HttpServletRequest request) {
        return this.processTransferAction(request);
    }
    
    private String processTransferAction(HttpServletRequest request) {
        Model model = (Model) request.getAttribute("model");
        bank.logic.Model domainModel = bank.logic.Model.instance();
        HttpSession session = request.getSession(true);
        Usuario usuario = (Usuario) session.getAttribute("user");
        Cliente cliente;
        try {// working . . . here
            cliente = domainModel.clienteFind(usuario);
            //validar datos completos ************************************
            String monto = request.getParameter("monto");
            //HashMap parametros = (HashMap) request.getParameterMap();//ver todos los parametros
            String num1 = request.getParameter("cuentaOrigen");
            Cuenta origen = domainModel.cuentaFind(Integer.parseInt(num1));
            //validar si tiene el monto para la transferencia
            String num2 = request.getParameter("cuentaDestino");
            Cuenta destino = domainModel.cuentaFind(Integer.parseInt(num2));
            model.setOrigin_account(origen);
            model.setDestination_account(destino);
            model.setOrigin_accounts(domainModel.cuentasFind(cliente));
            model.setDestination_accounts(domainModel.cuentasVinculadasFind(cliente));
            model.setMonto(Integer.parseInt(monto));
            //setear los datos en el model para que pueda confirmar si todo es correcto
            return "/presentation/cliente/transferencias/View.jsp";
        } catch (Exception ex) {
            return "";
        }
    }

    
    private String transfer(HttpServletRequest request) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
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
