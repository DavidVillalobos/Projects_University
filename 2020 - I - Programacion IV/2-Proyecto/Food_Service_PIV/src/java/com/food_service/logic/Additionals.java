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
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

/**
 *
 * @author Home
 */
@Entity
@Table(name = "additionals")
@NamedQueries({
    @NamedQuery(name = "Additionals.findAll", query = "SELECT a FROM Additionals a")})
public class Additionals implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 45)
    @Column(name = "name")
    private String name;
    @Basic(optional = false)
    @NotNull
    @Column(name = "type")
    private short type;
    @Column(name = "mandatory")
    private Short mandatory;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "additionals")
    private List<ClienteAdditionals> clienteAdditionalsList;
    @JoinColumn(name = "dish", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Dishes dishes;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "additionals")
    private List<Details> detailsList;

    public Additionals() {
    }

    public Additionals(Integer id) {
        this.id = id;
    }

    public Additionals(Integer id, String name, short type) {
        this.id = id;
        this.name = name;
        this.type = type;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public short getType() {
        return type;
    }

    public void setType(short type) {
        this.type = type;
    }

    public Short getMandatory() {
        return mandatory;
    }

    public void setMandatory(Short mandatory) {
        this.mandatory = mandatory;
    }

    public List<ClienteAdditionals> getClienteAdditionalsList() {
        return clienteAdditionalsList;
    }

    public void setClienteAdditionalsList(List<ClienteAdditionals> clienteAdditionalsList) {
        this.clienteAdditionalsList = clienteAdditionalsList;
    }

    public Dishes getDishes() {
        return dishes;
    }

    public void setDishes(Dishes dishes) {
        this.dishes = dishes;
    }

    public List<Details> getDetailsList() {
        return detailsList;
    }

    public void setDetailsList(List<Details> detailsList) {
        this.detailsList = detailsList;
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
        if (!(object instanceof Additionals)) {
            return false;
        }
        Additionals other = (Additionals) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "food_service.logic.Additionals[ id=" + id + " ]";
    }
    
}
