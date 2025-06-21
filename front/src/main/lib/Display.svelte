<script lang="ts">
    import Pixel from './Pixel.svelte'
    import { currentDisplay, fetchDisplay, updateDisplay } from '../display'
    import { fetchTheme } from '../theme';
    import { onMount } from 'svelte';

    let isDrawing = false;

    function togglePixel(x: number, y: number) {
        $currentDisplay[x][y] = !$currentDisplay[x][y];
        $currentDisplay = [...$currentDisplay.map(row => [...row])];
        updateDisplay();
    }

    onMount(async () => {
        await fetchDisplay();  
        await fetchTheme();  
    });

    function startDrawing(x: number, y: number){
        isDrawing = true;
        togglePixel(x, y);
    }

    function endDrawing(){
        isDrawing = false;
    }

    function Draw(x: number, y: number){
        if(isDrawing){
            togglePixel(x, y);
        }
    }

</script>

<div class="flex flex-col items-center bg-black gap-3 p-1 rounded-xl shadow-2xl shadow-black" role="button" onmouseup={endDrawing} tabindex=0>
{#each $currentDisplay as row, rowIndex}
    <div class="flex flex-row gap-3" >
        {#each row as pixel, pixelIndex}
            <Pixel lit={pixel} 
                onClick={() => togglePixel(rowIndex, pixelIndex)} 
                onMouseDown={() => startDrawing(rowIndex, pixelIndex)}
                onMouseUp={() => endDrawing()}
                onMouseEnter={() => Draw(rowIndex, pixelIndex)}
                onTouchMove={() => Draw(rowIndex, pixelIndex)}
            />
        {/each}
    </div>
{/each}
</div>