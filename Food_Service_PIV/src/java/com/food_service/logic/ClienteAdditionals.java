/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.food_service.logic;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;

/**
 *
 * @author Home
 */
@Entity
@Table(name = "cliente_additionals")
@NamedQueries({
    @NamedQuery(name = "ClienteAdditionals.findAll", query = "SELECT c FROM ClienteAdditionals c")})
public class ClienteAdditionals implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @JoinColumn(name = "additional", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Additionals additionals; //Got it
    @JoinColumn(name = "client_dish", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private ClientDish clientDish; // Id needed
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "clienteAdditionals")
    private List<ClienteDetails> clienteDetailsList; //got it

    public ClienteAdditionals() {
    }

    public ClienteAdditionals(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Additionals getAdditionals() {
        return additionals;
    }

    public void setAdditionals(Additionals additionals) {
        this.additionals = additionals;
    }

    public ClientDish getClientDish() {
        return clientDish;
    }

    public void setClientDish(ClientDish clientDish) {
        this.clientDish = clientDish;
    }

    public List<ClienteDetails> getClienteDetailsList() {
        return clienteDetailsList;
    }

    public void setClienteDetailsList(List<ClienteDetails> clienteDetailsList) {
        this.clienteDetailsList = clienteDetailsList;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof ClienteAdditionals)) {
            return false;
        }
        ClienteAdditionals other = (ClienteAdditionals) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "food_service.logic.ClienteAdditionals[ id=" + id + " ]";
    }
    
}
