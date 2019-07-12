package com.linhaibin.chessTest;

import static org.junit.Assert.*;

import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import com.linhaibin.chess.CannonPiece;
import com.linhaibin.chess.Move;
import com.linhaibin.chess.State;
import com.linhaibin.chess.PieceMove;

public class CannonMoveTest {

	private State state;
	private CannonPiece cannonPiece;

	@Before
	public void setUp() throws Exception {
		state = new State();
		cannonPiece = new CannonPiece(25);
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testGenerateAllSimple() {
		int fromX = 1;
		int fromY = 7;
		List<Move> newMoveList = cannonPiece.generateAllMove(state, fromX, fromY);
		assertEquals(newMoveList.size(), 12);
	}

	@Test
	public void testGenerateNumberAllMid() {
		int fromX = 1;
		int fromY = 7;
		int toX = 4;
		int toY = 7;

		State midState = PieceMove.movePiece(state, fromX, fromY, toX, toY);
		List<Move> newMoveList = cannonPiece.generateAllMove(midState, toX, toY);
		assertEquals(8,newMoveList.size());
	}

	
	
	@Test
	public void testLegalMove() {
		int fromX = 1;
		int fromY = 7;
		int toX = 1;
		int toY = 5;
		assertEquals(true,cannonPiece.isLegalMove(state, fromX, fromY, toX, toY));
	}
	

	@Test
	public void testLegalMoveSuicide() {
		int fromX = 1;
		int fromY = 7;
		int toX = 1;
		int toY = 9;
		
		State midState = PieceMove.movePiece(state, fromX, fromY, toX, toY);
		
		int toXFinal = 1;
		int toYFinal = 9;
		assertEquals(false,cannonPiece.isLegalMove(midState, toX, toY, toXFinal, toYFinal));
	}
	
	
	@Test
	public void testIllegalMove() {
		int fromX = 1;
		int fromY = 7;
		int toX = 1;
		int toY = 2;
		
		assertEquals(false,cannonPiece.isLegalMove(state, fromX, fromY, toX, toY));
	}
	
	
	@Test
	public void testIllegalMoveAcross() {
		int fromX = 1;
		int fromY = 7;
		int toX = 1;
		int toY = 1;
		
		assertEquals(false,cannonPiece.isLegalMove(state, fromX, fromY, toX, toY));
	}
	
	@Test
	public void testLegalMoveWithObstacle() {
		int fromX = 1;
		int fromY = 7;
		int toX = 1;
		int toY = 0;
		
		assertEquals(true,cannonPiece.isLegalMove(state, fromX, fromY, toX, toY));
	}
	
	
	
}
