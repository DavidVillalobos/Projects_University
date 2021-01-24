/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bank.logic;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

/**
 *
 * @author David Villalobos
 */
@Entity
@Table(name = "moneda")
@NamedQueries({
    @NamedQuery(name = "Moneda.findAll", query = "SELECT m FROM Moneda m")})
public class Moneda implements Serializable {

    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "nombreMoneda")
    private String nombreMoneda;
    
    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 3)
    @Column(name = "idMoneda")
    private String idMoneda;
    @Basic(optional = false)
    @NotNull
    @Column(name = "valorColones")
    private double valorColones;
    @Basic(optional = false)
    @NotNull
    @Column(name = "interes")
    private double interes;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "moneda")
    private List<Cuenta> cuentaList;

    public Moneda() {
    }

    public Moneda(String idMoneda) {
        this.idMoneda = idMoneda;
    }

    public Moneda(String idMoneda, String nombreMoneda, double valorColones, double interes) {
        this.idMoneda = idMoneda;
        this.nombreMoneda = nombreMoneda;
        this.valorColones = valorColones;
        this.interes = interes;
    }

    public String getIdMoneda() {
        return idMoneda;
    }

    public void setIdMoneda(String idMoneda) {
        this.idMoneda = idMoneda;
    }

    public double getValorColones() {
        return valorColones;
    }

    public void setValorColones(double valorColones) {
        this.valorColones = valorColones;
    }

    public double getInteres() {
        return interes;
    }

    public void setInteres(double interes) {
        this.interes = interes;
    }

    public List<Cuenta> getCuentaList() {
        return cuentaList;
    }

    public void setCuentaList(List<Cuenta> cuentaList) {
        this.cuentaList = cuentaList;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idMoneda != null ? idMoneda.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Moneda)) {
            return false;
        }
        Moneda other = (Moneda) object;
        if ((this.idMoneda == null && other.idMoneda != null) || (this.idMoneda != null && !this.idMoneda.equals(other.idMoneda))) {
            return false;
        }
        return true;
    }

    public String getNombreMoneda() {
        return nombreMoneda;
    }

    public void setNombreMoneda(String nombreMoneda) {
        this.nombreMoneda = nombreMoneda;
    }
    
    @Override
    public String toString() {
        return nombreMoneda;
    }
}
