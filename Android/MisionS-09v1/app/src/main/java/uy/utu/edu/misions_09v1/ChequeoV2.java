package uy.utu.edu.misions_09v1;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class ChequeoV2 extends AppCompatActivity {
    Button bt_chqIOIO;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chequeo_v2);

        bt_chqIOIO = (Button) findViewById(R.id.bt_cheqIOIO);
        bt_chqIOIO.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                IrAChequeoIOIO(view);
            }
        });
    }
    private void IrAChequeoIOIO(View v){
        Intent intento = new Intent(this, ChequearIOIO.class);
        startActivity(intento);
    }
}
