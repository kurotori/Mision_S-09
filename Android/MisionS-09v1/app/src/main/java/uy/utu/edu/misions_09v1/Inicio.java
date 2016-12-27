package uy.utu.edu.misions_09v1;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;


public class Inicio extends AppCompatActivity {

    Button bt_chequear;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_inicio);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);



        bt_chequear = (Button) findViewById(R.id.bt_chequear);
        bt_chequear.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                IrAChequeo(v);
                //IdPantalla("Chequear Componentes");

                    }
                }
            );

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "S-09 v1 \u00a9 2016, Club AeroEspacial de la\nEscuela Técnica de Melo", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });


    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_inicio, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private void IdPantalla(final String pantalla){
        runOnUiThread(new Runnable() {
            @Override
            public void run() {

            }
        });
    }

    private void IrAChequeo(View v){
        Intent intento = new Intent(this, ChequeoV2.class);
        startActivity(intento);
    }


}
