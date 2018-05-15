package uy.utu.edu.misions_09v1;


//Para IOIO
import android.content.Context;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

import ioio.lib.api.DigitalOutput;
import ioio.lib.api.IOIO;
import ioio.lib.api.IOIO.VersionType;
import ioio.lib.api.Uart;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.util.IOIOBaseApplicationHelper;
import ioio.lib.util.BaseIOIOLooper;
import ioio.lib.util.android.IOIOActivity;
import ioio.lib.util.IOIOLooper;

public class ChequearIOIO extends IOIOActivity {
    IOIO ioio;
    TextView tv_chequeo;
    boolean chequearIOIO = false;
    private InputStream datosNanoIN;
    private OutputStream datosNanoOUT;
    BufferedReader lector;
    StringBuilder constructor;
    InputStreamReader recolector;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chequear_ioio);

        tv_chequeo = (TextView) findViewById(R.id.tv_chequeo);


    }

    class Looper extends BaseIOIOLooper{
        private Uart serialNano;
        private DigitalOutput led_;
        @Override
        protected void setup() throws ConnectionLostException {

            //showVersions(ioio_, "Placa IOIO conectada");
            datosIOIO(ioio_);

            try {
                serialNano = ioio_.openUart(13, 14, 9600, Uart.Parity.NONE, Uart.StopBits.ONE);
                //datosNanoIN --> los datos que llegan DESDE el Nano
                datosNanoIN = serialNano.getInputStream();
                mostrarAviso("\nUART IN iniciado");

                //datosNanoOUT --> los datos que van HACIA el Nano
                datosNanoOUT = serialNano.getOutputStream();
                mostrarAviso("\nUART OUT iniciado");

            } catch (IllegalArgumentException e) {
                mostrarAviso("\nNo se pudo iniciar UART. Error" + e.toString());
            }
            recolector = new InputStreamReader(datosNanoIN);

            try{
                String comando = "s\n";
                datosNanoOUT.write(comando.getBytes());
                mostrarAviso("\nSolicitando datos al" +
                        "" +
                        " ARDUINO");
            }
            catch (IOException e){
                mostrarAviso("\nERROR: "+e.toString());
            }



        }


        /**
         * Called repetitively while the IOIO is connected.
         *
         * @throws ConnectionLostException
         *             When IOIO connection is lost.
         * @throws InterruptedException
         * 				When the IOIO thread has been interrupted.
         *
         * @see ioio.lib.util.IOIOLooper#loop()
         */
        @Override
        public void loop() throws ConnectionLostException, InterruptedException {
                //mostrarAviso("- - -");

            mostrarAviso("\nEsperando respuesta...");
            try {
                if (datosNanoIN.available() > 0) {
                    String dato="";
                    //IOIOConnectionManager.Thread.sleep(5000);
                    lector = new BufferedReader(recolector);
                    while ((dato = lector.readLine()) != null) {

                        mostrarAviso("\n"+dato);

                    }

                } else {
                   // mostrarAviso("UART Sin Datos");
                }

            } catch (IOException e) {
                mostrarAviso("\n"+e.toString());
            }




            Thread.sleep(5000);
        }

        /**
         * Called when the IOIO is disconnected.
         *
         * @see ioio.lib.util.IOIOLooper#disconnected()
         */
        @Override
        public void disconnected() {
            toast("IOIO desconectada");
        }

        /**
         * Called when the IOIO is connected, but has an incompatible firmware version.
         *
         * @see ioio.lib.util.IOIOLooper#incompatible(IOIO)
         */
        @Override
        public void incompatible() {
            showVersions(ioio_, "Firmware Incompatible");
        }

    }
    @Override
    protected IOIOLooper createIOIOLooper() {
        return new Looper();
    }
    private void showVersions(IOIO ioio, String title) {
        toast(String.format("%s\n" +
                        "IOIOLib: %s\n" +
                        "Application firmware: %s\n" +
                        "Bootloader firmware: %s\n" +
                        "Hardware: %s",
                title,
                ioio.getImplVersion(VersionType.IOIOLIB_VER),
                ioio.getImplVersion(VersionType.APP_FIRMWARE_VER),
                ioio.getImplVersion(VersionType.BOOTLOADER_VER),
                ioio.getImplVersion(VersionType.HARDWARE_VER)));
    }


    /**
     * A method to create our IOIO thread.
     *
     * @see ioio.lib.util.AbstractIOIOActivity#createIOIOThread()
     */


    private void datosIOIO(IOIO ioio){


        final String hardVer = ioio.getImplVersion(VersionType.HARDWARE_VER);
        final String bootVer = ioio.getImplVersion(VersionType.BOOTLOADER_VER);
        final String libVer = ioio.getImplVersion(VersionType.IOIOLIB_VER);
        final String firmVer = ioio.getImplVersion(VersionType.APP_FIRMWARE_VER);
        final String IOIOstatus = ioio.getState().toString();
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                tv_chequeo.setText("Buscando una placa IOIO...");
                if(IOIOstatus.equals("CONNECTED")){
                    tv_chequeo.setText(
                            "Se ha detectado una placa IOIO:"+"\n"+
                            "Hardware: "+hardVer+"\n"+
                            "Bootloader: "+bootVer+"\n"+
                            "Librería IOIO: "+libVer+"\n"+
                            "Firmware: "+firmVer
                    );
                }
                else{
                    tv_chequeo.setText("No se detecta la placa IOIO.");
                }
                chequearIOIO=false;

            }
        });
    }

    private void toast(final String message) {
        final Context context = this;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(context, message, Toast.LENGTH_LONG).show();
            }
        });
    }

    private void chequearIOIO(){
        if(chequearIOIO=false){
            chequearIOIO=true;
        }

    }

    private void mostrarAviso(final String aviso){
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                tv_chequeo.append(aviso);
            }
        });
    }

}
