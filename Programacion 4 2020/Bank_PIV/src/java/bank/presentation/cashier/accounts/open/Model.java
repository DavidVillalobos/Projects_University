package bank.presentation.cashier.accounts.open;

import bank.logic.Cliente;
import bank.logic.Cuenta;
import bank.logic.Moneda;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Model {
    
    private Cuenta account;
    private Cliente client;
    private List<Moneda> monedas;
    private Boolean registrated;

    public Model() {
        this.account = new Cuenta();
        this.client = new Cliente();
        this.monedas = new ArrayList<>();
        this.registrated = true;
    }

    public Cuenta getAccount() {
        return account;
    }

    public void setAccount(Cuenta account) {
        this.account = account;
    }

    public Cliente getClient() {
        return client;
    }

    public void setClient(Cliente client) {
        this.client = client;
    }

    public List<Moneda> getMonedas() {
        return monedas;
    }

    public void setMonedas(List<Moneda> monedas) {
        this.monedas = monedas;
    }

    public Boolean getRegistrated() {
        return registrated;
    }

    public void setRegistrated(Boolean registrated) {
        this.registrated = registrated;
    }
    
}
