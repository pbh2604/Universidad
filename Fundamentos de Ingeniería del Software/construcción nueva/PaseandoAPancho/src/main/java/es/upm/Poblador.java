package es.upm;

import es.upm.Controladora.*;
import es.upm.Modelo.*;

import java.util.LinkedList;
import java.time.LocalDateTime;
import java.time.ZoneOffset;

public class Poblador {

    private CCuidador controladorCuidador;
    private CResponsable controladorResponsable;
    private CCuidados controladorCuidado;

    private LinkedList<Mascota> listaResponsable1;
    private LinkedList<Mascota> listaResponsable2;

    LocalDateTime fecha1 = LocalDateTime.of(2024, 5, 12, 10, 30);
    long fechaEnMilisegundos1 = fecha1.toInstant(ZoneOffset.UTC).toEpochMilli();
    LocalDateTime fecha2 = LocalDateTime.of(2024, 6, 8, 15, 30);
    long fechaEnMilisegundos2 = fecha2.toInstant(ZoneOffset.UTC).toEpochMilli();

    Mascota mascota1 = new Mascota("Frida", "123Calle", "Guapa", "LR56", "6789");
    Mascota mascota2 = new Mascota("Rita", "456Avenida", "Gorda", "GT42", "2345");
    Mascota mascota3 = new Mascota("Milka", "789Bulevar", "Pequeña", "PM98", "0987");
    Mascota mascota4 = new Mascota("Limon", "012Rotonda", "Flaco", "FR12", "6543");


    public Poblador(CCuidador controladorCuidador, CResponsable controladorResponsable, CCuidados controladorCuidado) {
        this.controladorCuidador = controladorCuidador;
        this.controladorResponsable = controladorResponsable;
        this.controladorCuidado = controladorCuidado;
    }

    public void poblarDatos() {
        listaCuidadoresManualmente();
        listaMascotasManualmente();
        listaResponsablesManualmente();
        listaCuidadosManualmente();
    }


    private void listaCuidadoresManualmente() {

        Cuidador cuidador1 = new Cuidador("fef2eeda89934315627e1f77f888b817", "Mesi", TPlataforma.FACEBOOK);
        //pwd: Mesi
        Cuidador cuidador2 = new Cuidador("0fee275ebba255bd57a43fc991edef38", "Isa", TPlataforma.FACEBOOK);
        //pwd: Isa

        controladorCuidador.agregarCuidador(cuidador1);
        controladorCuidador.agregarCuidador(cuidador2);
    }

    private void listaMascotasManualmente() {
        listaResponsable1 = new LinkedList<>();
        listaResponsable2 = new LinkedList<>();

        listaResponsable1.add(mascota1);
        listaResponsable1.add(mascota2);

        listaResponsable2.add(mascota3);
        listaResponsable2.add(mascota4);

    }

    private void listaResponsablesManualmente() {
        Responsable responsable1 = new Responsable("ec02bbae1151a771e9bf144edf4f3747", "Almu", TPlataforma.FACEBOOK, listaResponsable1);
        //pwd:Almu
        Responsable responsable2 = new Responsable("ed6648c87aaffff3dc0361efc1ee921a", "Blas", TPlataforma.FACEBOOK, listaResponsable2);
        //pwd:Blas

        controladorResponsable.agregarResponsable(responsable1);
        controladorResponsable.agregarResponsable(responsable2);
    }

    private void listaCuidadosManualmente() {


        Cuidado cuidado1 = new Cuidado(15.5, 33, fechaEnMilisegundos1, 30, 28033, null, null, null, mascota1);
        Cuidado cuidado2 = new Cuidado(16.5, 66, fechaEnMilisegundos2, 25, 27055, null, null, null, mascota2);

        controladorCuidado.agregarCuidado(cuidado1);
        controladorCuidado.agregarCuidado(cuidado2);

    }

}
