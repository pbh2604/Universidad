package es.upm;

import es.upm.Controladora.CCuidador;
import es.upm.Controladora.CResponsable;
import es.upm.Modelo.Mascota;
import es.upm.Modelo.Responsable;
import es.upm.Modelo.TPlataforma;
import es.upm.Modelo.Usuario;
import es.upm.Vista.IVistas.IVistaResponsable;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mock;
import servidor.ExternalRRSS;
import org.mockito.MockitoAnnotations;
import static org.junit.Assert.*;
import static org.mockito.Mockito.*;

public class CResponsableTest {

    private CResponsable cResponsable;
    private CCuidador hermana;

    @Before
    public void setUp(){
        hermana = mock(CCuidador.class);
        cResponsable = new CResponsable(hermana);
    }

    @Test
    public void testLogin(){
        Usuario resultado = cResponsable.login("ed6648c87aaffff3dc0361efc1ee921a");
        assertNotNull(resultado);
        assertEquals("Blas", resultado.getNombre());
        assertEquals("ed6648c87aaffff3dc0361efc1ee921a", resultado.getId());
    }

    @Test
    public void testLoginResponosableNoExistente(){
        Usuario usuario = cResponsable.login("yuifryu76");
        assertNull(usuario);
    }

    @Test
    public void testAgregarMascota(){
        Responsable responsable = new Responsable("id4575", "Jose", TPlataforma.FACEBOOK);
        cResponsable.agregarResponsable(responsable);
        Mascota mascota = new Mascota("Frida", "Av. 123", "Descri.", "RIAC987", "POL908");
        agregarMascota(responsable, mascota);
        assertTrue(responsable.getMascotas().contains(mascota));
    }

    private void agregarMascota(Responsable responsable, Mascota mascota) {
        responsable.addMascota(mascota);
    }

    @Test
    public void testListarMascotasConMascotas(){
        Responsable responsable = new Responsable("id123", "Almu", TPlataforma.FACEBOOK);
        Mascota mascota = new Mascota("Cobi", "Calle 123", "Descripcion", "RIAC123", "POL1Z4");
        responsable.addMascota(mascota);
        Usuario logueado = responsable;
        cResponsable.listarMascotas(logueado);
    }

    @Test
    public void testListarMascotasSinMascotas(){
        Usuario logueado = new Responsable("id1246", "Mesi", TPlataforma.FACEBOOK);
        cResponsable.listarMascotas(logueado);
    }

    @Test
    public void testCrearUsuarioIDVacio(){
        String name = "Almu";
        String id = "";
    }
}