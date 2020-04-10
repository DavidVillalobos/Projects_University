package bank.presentation.client.transfers;

import bank.logic.Cuenta;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Model {
    private List<Cuenta> origin_accounts;
    private List<Cuenta> destination_accounts;
    private Cuenta origin_account;
    private Cuenta destination_account;
    private double monto;
    private String motivo;
    
    public Model() {
        origin_accounts = new ArrayList<>();
        destination_accounts = new ArrayList<>();
        origin_account = null;
        destination_account = null;
        motivo = "";
    }

    public String getMotivo() {
        return motivo;
    }

    public void setMotivo(String motivo) {
        this.motivo = motivo;
    }

    public List<Cuenta> getOrigin_accounts() {
        return origin_accounts;
    }

    public void setOrigin_accounts(List<Cuenta> origin_accounts) {
        this.origin_accounts = origin_accounts;
    }

    public List<Cuenta> getDestination_accounts() {
        return destination_accounts;
    }

    public void setDestination_accounts(List<Cuenta> destination_accounts) {
        this.destination_accounts = destination_accounts;
    }

    public Cuenta getOrigin_account() {
        return origin_account;
    }

    public void setOrigin_account(Cuenta origin_account) {
        this.origin_account = origin_account;
    }

    public Cuenta getDestination_account() {
        return destination_account;
    }

    public void setDestination_account(Cuenta destination_account) {
        this.destination_account = destination_account;
    }

    public double getMonto() {
        return monto;
    }

    public void setMonto(double monto) {
        this.monto = monto;
    }
    
}
