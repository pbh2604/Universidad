package es.upm.Modelo;


public class Animal_exotico extends Mascota {
    private String certificado;

    public Animal_exotico(String nombre, String domicilio, String descripcion, String RIAC, String numero_poliza, String certificado) {
        super(nombre, domicilio, descripcion, RIAC, numero_poliza);
        this.certificado = certificado;
    }

    public String getCertificado() {
        return certificado;
    }

    public void setCertificado(String certificado) {
        this.certificado = certificado;
    }
}
