package com.linhaibin.chess;

import java.util.Arrays;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;

public class Evaluate {

	public Evaluate() {
		
	}

	public static final List<Integer> redKingPositionValue = Arrays.asList(
			0,0,0,0,0,0,0,0,0,   
			0,0,0,0,0,0,0,0,0,     
			0,0,0,0,0,0,0,0,0,   
			0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,     
			
			0,0,0,0,0,0,0,0,0,     
			0,0,0,0,0,0,0,0,0,
			0,0,0,1,1,1,0,0,0,    
			0,0,0,10,10,10,0,0,0,    
			0,0,0,15,20,15,0,0,0);
	
	public static final List<Integer> blackKingPositionValue = Arrays.asList(
			0,0,0,15,20,15,0,0,0,   
			0,0,0,10,10,10,0,0,0,  
			0,0,0,1,1,1,0,0,0,
			0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,     
			
			0,0,0,0,0,0,0,0,0,     
			0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,       
			0,0,0,0,0,0,0,0,0,       
			0,0,0,0,0,0,0,0,0);
	
	public static final List<Integer> redRookPositionValue = Arrays.asList(

			160,170,160,150,150,150,160,170,160,   
			170,180,170,190,250,190,170,180,170,     
			170,190,200,220,240,220,200,190,170,   
			180,220,210,240,250,240,210,220,180,
			180,220,210,240,250,240,210,220,180,     
			
			180,220,210,240,250,240,210,220,180,
			170,190,200,220,240,220,200,190,170,
			170,180,170,170,160,170,170,180,170,
			160,170,160,160,150,160,160,170,160,    
			150,160,150,160,150,160,150,160,150);
	
	public static final List<Integer> blackRookPositionValue = Arrays.asList(
			150,160,150,160,150,160,150,160,150,
			160,170,160,160,150,160,160,170,160,    
			170,180,170,170,160,170,170,180,170,
			170,190,200,220,240,220,200,190,170,
			180,220,210,240,250,240,210,220,180,
			
			180,220,210,240,250,240,210,220,180,
			180,220,210,240,250,240,210,220,180,
			170,190,200,220,240,220,200,190,170,
			170,180,170,190,250,190,170,180,170,   
			160,170,160,150,150,150,160,170,160);
	
	public static final List<Integer> redAdvisorPositionValue = Arrays.asList(
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,30,0,30,0,0,0,
		     0,0,0,0,22,0,0,0,0,
		     0,0,0,30,0,30,0,0,0);
	
	public static final List<Integer> blackAdvisorPositionValue = Arrays.asList(
			 0,0,0,30,0,30,0,0,0,
		     0,0,0,0,22,0,0,0,0,
		     0,0,0,30,0,30,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0);
	
	public static final List<Integer> redBishopPositionValue = Arrays.asList(
			0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
			
	        0,0,25,0,0,0,25,0,0,
	        0,0,0,0,0,0,0,0,0,
	        20,0,0,0,35,0,0,0,20,
	        0,0,0,0,0,0,0,0,0,
	        0,0,30,0,0,0,30,0,0);
	
	public static final List<Integer> blackBishopPositionValue = Arrays.asList(
			0,0,30,0,0,0,30,0,0,
	        0,0,0,0,0,0,0,0,0,
	        20,0,0,0,35,0,0,0,20,
	        0,0,0,0,0,0,0,0,0,
	        0,0,25,0,0,0,25,0,0,
	        
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0);
	
	public static final List<Integer> redKnightPositionValue = Arrays.asList(
			70,80,90,80,70,80,90,80,70,
			80,110,125,90,70,90,125,110,80,
			90,100,120,125,120,125,120,100,90,
			90,100,120,130,110,130,120,100,90,
			90,110,110,120,100,120,110,110,90,
			
			90,100,100,110,100,110,100,100,90,
			80,90,100,100,90,100,100,90,80,
			80,80,90,90,80,90,90,80,80,
			70,75,75,70,50,70,75,75,70,
			60,70,75,70,60,70,75,70,60);
	
	public static final List<Integer> blackKnightPositionValue = Arrays.asList(
			60,70,75,70,60,70,75,70,60,
	        70,75,75,70,50,70,75,75,70,
	        80,80,90,90,80,90,90,80,80,
	        80,90,100,100,90,100,100,90,80,
	        90,100,100,110,100,110,100,100,90,
	        
	        90,110,110,120,100,120,110,110,90,
	        90,100,120,130,110,130,120,100,90,
	        90,100,120,125,120,125,120,100,90,
	        80,110,125,90,70,90,125,110,80,
	        70,80,90,80,70,80,90,80,70);
	
	public static final List<Integer> redPondPositionValue = Arrays.asList(
			10,10,10,20,25,20,10,10,10,
			25,30,40,50,60,50,40,30,25,
			25,30,30,40,40,40,30,30,25,
			20,25,25,30,30,30,25,25,20,
			15,20,20,20,20,20,20,20,15,
			
			10,0,15,0,15,0,15,0,10,
			10,0,10,0,15,0,10,0,10,
			0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0);
	
	public static final List<Integer> blackPondPositionValue = Arrays.asList(
			0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        0,0,0,0,0,0,0,0,0,
	        10,0,10,0,15,0,10,0,10,
	        10,0,15,0,15,0,15,0,10,
	        
	        15,20,20,20,20,20,20,20,15,
	        20,25,25,30,30,30,25,25,20,
	        25,30,30,40,40,40,30,30,25,
	        25,30,40,50,60,50,40,30,25,
	        10,10,10,20,25,20,10,10,10);
	
	public static final List<Integer> redCannonPositionValue = Arrays.asList(
			125,130,100,70,60,70,100,130,125,
			110,125,100,70,60,70,100,125,110,
			100,120,90,80,80,80,90,120,100,
			90,110,90,110,130,110,90,110,90,
			90,110,90,110,130,110,90,110,90,
			
			90,100,90,110,130,110,90,100,90,
			90,100,90,90,110,90,90,100,90,
			90,100,80,80,70,80,80,100,90,
			80,90,80,70,65,70,80,90,80,
			80,90,80,70,60,70,80,90,80);
	
	public static final List<Integer> blackCannonPositionValue = Arrays.asList(
			80,90,80,70,60,70,80,90,80,
	        80,90,80,70,65,70,80,90,80,
	        90,100,80,80,70,80,80,100,90,
	        90,100,90,90,110,90,90,100,90,
	        90,100,90,110,130,110,90,100,90,
	        
	        90,110,90,110,130,110,90,110,90,
	        90,110,90,110,130,110,90,110,90,
	        100,120,90,80,80,80,90,120,100,
	        110,125,100,70,60,70,100,125,110,
	        125,130,100,70,60,70,100,130,125);
	
	
	public static int evaluateState(State state){
		int value = 0;
		value += evaluateStatic(state);
		value += evaluateMobility(state);
		value += evaluateExistence(state);
		return value;
	}
	
	private static int evaluateStatic(State state){
		int staticValue = 0;
		Collection<Piece> pieceList = state.getPieceList().values();
		Iterator<Piece> it = pieceList.iterator();
		while(it.hasNext()){
			Piece piece = it.next();
			staticValue += piece.evaluateStatic(piece.getX(), piece.getY());
		}
		return staticValue;
	}
	
	private static int evaluateExistence(State state){
		int existenceValue = 0;
		Collection<Piece> pieceList = state.getPieceList().values();
		Iterator<Piece> it = pieceList.iterator();
		while(it.hasNext()){
			Piece piece = it.next();
			existenceValue += piece.evaluateExistence();
		}
		return existenceValue;
	}
	
	private static int evaluateMobility(State state){
		int mobilityValue = 0;
		Collection<Piece> pieceList = state.getPieceList().values();
		Iterator<Piece> it = pieceList.iterator();
		while(it.hasNext()){
			Piece piece = it.next();
			mobilityValue += piece.evaluateMobility(state, piece.getX(), piece.getY());
		}
		return mobilityValue;
	}
	
}
