package com.example.crazyrummy;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;



public class MainActivity extends Activity implements OnClickListener {
	// Player 1
	Button add_5_p1;
	Button add_10_p1;
	Button add_ace_p1;

	TextView player_1;
	TextView player_1_score;

	int counter_p1 = 0;

	// Player 2
	Button add_5_p2;
	Button add_10_p2;
	Button add_ace_p2;

	TextView player_2;
	TextView player_2_score;

	int counter_p2 = 0;

	// Player 3
	Button add_5_p3;
	Button add_10_p3;
	Button add_ace_p3;

	TextView player_3;
	TextView player_3_score;

	int counter_p3 = 0;

	// Reset & Finish Button
	Button reset;
	Button finish;

	// Intent stuff
	public static final String p1_score = "com.example.crazyrummy.p1";
	public static final String p2_score = "com.example.crazyrummy.p2";
	public static final String p3_score = "com.example.crazyrummy.p3";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		// Player 1
		add_5_p1 = (Button) findViewById(R.id.add_5_p1);
		add_10_p1 = (Button) findViewById(R.id.add_10_p1);
		add_ace_p1 = (Button) findViewById(R.id.add_ace_p1);
		player_1 = (TextView) findViewById(R.id.player_1);
		player_1_score = (TextView) findViewById(R.id.player_1_score);

		// Set on Click listeners on buttons
		add_5_p1.setOnClickListener(this);
		add_10_p1.setOnClickListener(this);
		add_ace_p1.setOnClickListener(this);

		// Player 2
		add_5_p2 = (Button) findViewById(R.id.add_5_p2);
		add_10_p2 = (Button) findViewById(R.id.add_10_p2);
		add_ace_p2 = (Button) findViewById(R.id.add_ace_p2);
		player_2 = (TextView) findViewById(R.id.player_2);
		player_2_score = (TextView) findViewById(R.id.player_2_score);

		// Set on Click listeners on buttons
		add_5_p2.setOnClickListener(this);
		add_10_p2.setOnClickListener(this);
		add_ace_p2.setOnClickListener(this);

		// Player 3
		add_5_p3 = (Button) findViewById(R.id.add_5_p3);
		add_10_p3 = (Button) findViewById(R.id.add_10_p3);
		add_ace_p3 = (Button) findViewById(R.id.add_ace_p3);
		player_3 = (TextView) findViewById(R.id.player_3);
		player_3_score = (TextView) findViewById(R.id.player_3_score);

		// Set on Click listeners on buttons
		add_5_p3.setOnClickListener(this);
		add_10_p3.setOnClickListener(this);
		add_ace_p3.setOnClickListener(this);

		// Change font size of the text
		player_1.setTextSize(TypedValue.COMPLEX_UNIT_SP, 24);
		player_1_score.setTextSize(TypedValue.COMPLEX_UNIT_SP, 24);
		player_1.setTextColor(Color.WHITE);
		player_1_score.setTextColor(Color.WHITE);

		player_2.setTextSize(TypedValue.COMPLEX_UNIT_SP, 24);
		player_2_score.setTextSize(TypedValue.COMPLEX_UNIT_SP, 24);
		player_2.setTextColor(Color.WHITE);
		player_2_score.setTextColor(Color.WHITE);

		player_3.setTextSize(TypedValue.COMPLEX_UNIT_SP, 24);
		player_3_score.setTextSize(TypedValue.COMPLEX_UNIT_SP, 24);
		player_3.setTextColor(Color.WHITE);
		player_3_score.setTextColor(Color.WHITE);

		// Reset & Finish Button
		reset = (Button) findViewById(R.id.reset_game);
		finish = (Button) findViewById(R.id.finish_game);

		// Set onClickListeners
		reset.setOnClickListener(this);
		finish.setOnClickListener(this);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void onClick(View v) {
		// Player 1
		if (v == add_5_p1) {
			counter_p1 += 5;
			player_1_score.setText(Integer.toString(counter_p1));
		}
		if (v == add_10_p1) {
			counter_p1 += 10;
			player_1_score.setText(Integer.toString(counter_p1));
		}
		if (v == add_ace_p1) {
			counter_p1 += 15;
			player_1_score.setText(Integer.toString(counter_p1));
		}

		// Player 2
		if (v == add_5_p2) {
			counter_p2 += 5;
			player_2_score.setText(Integer.toString(counter_p2));
		}
		if (v == add_10_p2) {
			counter_p2 += 10;
			player_2_score.setText(Integer.toString(counter_p2));
		}
		if (v == add_ace_p2) {
			counter_p2 += 15;
			player_2_score.setText(Integer.toString(counter_p2));
		}

		// Player 3
		if (v == add_5_p3) {
			counter_p3 += 5;
			player_3_score.setText(Integer.toString(counter_p3));
		}
		if (v == add_10_p3) {
			counter_p3 += 10;
			player_3_score.setText(Integer.toString(counter_p3));
		}
		if (v == add_ace_p3) {
			counter_p3 += 15;
			player_3_score.setText(Integer.toString(counter_p3));
		}
		if (v == reset) {
			counter_p1 = 0;
			counter_p2 = 0;
			counter_p3 = 0;
			player_1_score.setText(Integer.toString(counter_p1));
			player_2_score.setText(Integer.toString(counter_p2));
			player_3_score.setText(Integer.toString(counter_p3));
		}
		if (v == finish) {
			CreateSummaryActivity();
		}
	}

	void CreateSummaryActivity() {
		Intent summaryIntent = new Intent( this, SummaryActivity.class);
		
		summaryIntent.putExtra(p1_score, player_1_score.getText().toString());
		summaryIntent.putExtra(p2_score, player_2_score.getText().toString());
		summaryIntent.putExtra(p3_score, player_3_score.getText().toString());
		
		startActivity(summaryIntent);
		this.finish();
	}
}
