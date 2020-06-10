/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.food_service.logic;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;

/**
 *
 * @author Home
 */
@Entity
@Table(name = "cliente_details")
@NamedQueries({
    @NamedQuery(name = "ClienteDetails.findAll", query = "SELECT c FROM ClienteDetails c")})
public class ClienteDetails implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @JoinColumn(name = "cliente_additional", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private ClienteAdditionals clienteAdditionals;
    @JoinColumn(name = "detail", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Details details;

    public ClienteDetails() {
    }

    public ClienteDetails(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public ClienteAdditionals getClienteAdditionals() {
        return clienteAdditionals;
    }

    public void setClienteAdditionals(ClienteAdditionals clienteAdditionals) {
        this.clienteAdditionals = clienteAdditionals;
    }

    public Details getDetails() {
        return details;
    }

    public void setDetails(Details details) {
        this.details = details;
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
        if (!(object instanceof ClienteDetails)) {
            return false;
        }
        ClienteDetails other = (ClienteDetails) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "food_service.logic.ClienteDetails[ id=" + id + " ]";
    }
    
}
