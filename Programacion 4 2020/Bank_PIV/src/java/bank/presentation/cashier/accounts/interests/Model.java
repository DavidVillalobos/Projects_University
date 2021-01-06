package bank.presentation.cashier.accounts.interests;

import bank.logic.Moneda;
import bank.logic.Movimiento;
import java.util.List;

/**
 *
 * @author David Villalobos
 */
public class Model {
    private List<Moneda> monedas;
    private List<Movimiento> acreditas;

    public Model() {
        monedas = null;
        acreditas = null;
    }

    public List<Moneda> getMonedas() {
        return monedas;
    }

    public void setMonedas(List<Moneda> monedas) {
        this.monedas = monedas;
    }

    public List<Movimiento> getAcreditas() {
        return acreditas;
    }

    public void setAcreditas(List<Movimiento> acreditas) {
        this.acreditas = acreditas;
    }
    
}
