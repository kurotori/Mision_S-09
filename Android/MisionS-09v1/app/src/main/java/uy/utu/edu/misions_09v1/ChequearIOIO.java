package uy.utu.edu.misions_09v1;


//Para IOIO
import ioio.lib.api.DigitalOutput;
import ioio.lib.api.IOIO;
import ioio.lib.api.IOIO.VersionType;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.util.BaseIOIOLooper;
import ioio.lib.util.IOIOLooper;
import ioio.lib.util.android.IOIOActivity;
import android.content.Context;


import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class ChequearIOIO extends IOIOActivity {
    IOIO ioio;
    TextView tv_chequeo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chequear_ioio);

        tv_chequeo = (TextView) findViewById(R.id.tv_chequeo);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                  //      .setAction("Action", null).show();


            }
        });
    }

    class Looper extends BaseIOIOLooper{
        @Override
        protected void setup() throws ConnectionLostException {
            ioio = ioio_;
            showVersions(ioio_, "Placa IOIO connectada");
            datosIOIO(ioio_);
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

            Thread.sleep(100);
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

}
