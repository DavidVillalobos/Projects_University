package com.food_service.presentation;

import java.io.IOException;
import java.util.HashMap;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 *
 * @author David Villalobos ************************ EN IMPLEMENTACION AUN. . . . .
 */
@WebFilter(filterName = "AuthorizationFilter", urlPatterns = {"/*"})
public class AuthorizationFilter implements Filter {
    HashMap<String,String> protectedResources;

    public AuthorizationFilter(){
        protectedResources = new HashMap<>();
        protectedResources.put("GET /Personas/api/personas", "ADM-CLI"); // search
        protectedResources.put("GET /Personas/api/personas/", "ADM-CLI");  // edit
        protectedResources.put("POST /Personas/api/personas", "ADM"); // add
        protectedResources.put("PUT /Personas/api/personas", "ADM"); // update
        protectedResources.put("DELETE /Personas/api/personas/", "ADM"); // delete        
    }
    public void doFilter(ServletRequest request, ServletResponse response,FilterChain chain) throws IOException, ServletException {
        try {
            HttpServletRequest httpRequest = (HttpServletRequest) request;
            HttpServletResponse httpResponse = (HttpServletResponse) response;
            HttpSession session = httpRequest.getSession();
            String resource=httpRequest.getMethod()+" "+httpRequest.getRequestURI();
            String roles = getRoles(resource);
            if (roles==null) chain.doFilter(request, response);
            else{
                //Usuario usuario= (Usuario) session.getAttribute("usuario");
                if(null /*usuario*/==null) httpResponse.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                else
                    if(!roles.contains(/*usuario.getRol()*/ ""))
                        httpResponse.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                    else
                       chain.doFilter(request, response); 
            }
        } catch (Throwable t) {
            System.out.println("ERROR");
        }
    }
    
    String getRoles(String resource){
        for(String k: protectedResources.keySet()){
            if(resource.startsWith(k)) return  protectedResources.get(k);
        }
        return null;
    }
    
    public void init(FilterConfig fConfig) throws ServletException {
    }
    
    public void destroy(){ 
    }
}
