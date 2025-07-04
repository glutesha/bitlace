<script lang="ts">
    import { load, pushSaves, remove } from '../saves';
    import { deletetool } from '../delete';
    import PreviewPixel from './PreviewPixel.svelte';
    import { updateDisplay } from '../display';

    export let display: boolean[][];
    export let id: number;

    async function onClick(){
        if($deletetool){
            remove(id);
            await pushSaves();
        }
        else{
            load(id);
            await updateDisplay();
        }
    }
</script>

<button onclick={onClick} oncontextmenu={e => e.preventDefault()} class="flex shadow-md transition duration-200 ease-in-out max-h-42.5 flex-col items-center bg-black gap-1.5 p-[2px] rounded-md" 
    class:animate-jiggle={$deletetool} 
    class:shadow-red-700={$deletetool}>

{#each display as row}
    <div class="flex flex-row gap-1.5">
        {#each row as pixel}
            <PreviewPixel
                lit={pixel} 
            />
        {/each}
    </div>
{/each}
</button>