package bank.presentation.cashier.movements.deposit_withdrawal;

import bank.logic.Cuenta;
import bank.logic.Moneda;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Kevin Flores
 */
public class Model {
    private List<Cuenta> accounts;
    private Cuenta selected;
    private Moneda moneda;
    private String account_num;
    private String id_cliente;
    private String motivo;
    private Double monto;
    private String nombre_solicitante;
    private Integer tipoMovimiento;
    private List<Moneda> monedas;

    public Model() {
        this.accounts = new ArrayList<>();
        this.selected = null;
    }

    public Moneda getMoneda() {
        return moneda;
    }

    public void setMoneda(Moneda moneda) {
        this.moneda = moneda;
    }

    public List<Moneda> getMonedas() {
        return monedas;
    }

    public void setMonedas(List<Moneda> monedas) {
        this.monedas = monedas;
    }

    public List<Cuenta> getAccounts() {
        return accounts;
    }

    public void setAccounts(List<Cuenta> accounts) {
        this.accounts = accounts;
    }

    public Cuenta getSelected() {
        return selected;
    }

    public void setSelected(Cuenta selected) {
        this.selected = selected;
    }

    public String getAccount_num() {
        return account_num;
    }

    public void setAccount_num(String account_num) {
        this.account_num = account_num;
    }

    public String getId_cliente() {
        return id_cliente;
    }

    public void setId_cliente(String id_cliente) {
        this.id_cliente = id_cliente;
    }

    public String getMotivo() {
        return motivo;
    }

    public void setMotivo(String motivo) {
        this.motivo = motivo;
    }

    public Double getMonto() {
        return monto;
    }

    public void setMonto(Double monto) {
        this.monto = monto;
    }

    public String getNombre_solicitante() {
        return nombre_solicitante;
    }

    public void setNombre_solicitante(String nombre_solicitante) {
        this.nombre_solicitante = nombre_solicitante;
    }

    public Integer getTipoMovimiento() {
        return tipoMovimiento;
    }

    public void setTipoMovimiento(Integer tipoMovimiento) {
        this.tipoMovimiento = tipoMovimiento;
    }
    
  
}
