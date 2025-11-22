package es.upm.Modelo;

public class Mensaje {
    private String texto;
    private Usuario destinatario;
    private Usuario remitente;
    private Cuidado cuidado;

    public Mensaje(String texto, Usuario destinatario, Usuario remitente, Cuidado cuidado) {
        this.texto = texto;
        this.destinatario = destinatario;
        this.remitente = remitente;
        this.cuidado = cuidado;
    }

    public String getTexto() {
        return texto;
    }

    public void setTexto(String texto) {
        this.texto = texto;
    }

    public Usuario getDestinatario() {
        return destinatario;
    }

    public void setDestinatario(Usuario destinatario) {
        this.destinatario = destinatario;
    }

    public Usuario getRemitente() {
        return remitente;
    }

    public void setRemitente(Usuario remitente) {
        this.remitente = remitente;
    }

    public Cuidado getCuidado() {
        return cuidado;
    }

    public void setCuidado(Cuidado cuidado) {
        this.cuidado = cuidado;
    }
}
